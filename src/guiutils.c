#include "guiutils.h"

#include <SDL2/SDL.h>

#include "logutils.h"
#include "assertutils.h"
#include "floatutils.h"
#include "utils.h"

static const int GUI_PLOT_POINTS_NUM = 2000;
static const SDL_Point GUI_ORIGIN_DEFAULT = {0, 0};
static const int GUI_ORIGIN_MOVE_DELTA = 10;

typedef void(*event_callback_t)(SDL_Event* event);
struct gui_event_handler_t
{
    SDL_EventType event_type;
    event_callback_t callback;
};

static const int GUI_EVENT_HANDLER_BUFFER_SIZE = 10;

struct gui_event_buffer_t
{
    struct gui_event_handler_t* buffer;
    struct gui_event_handler_t* wr_ptr;
    struct gui_event_handler_t* rd_ptr;
    size_t size;
};

struct gui_object_t
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    int window_height;
    int window_width;

    SDL_Point* graph;
    SDL_Point origin;

    struct gui_event_buffer_t event_handlers;
    
    enum gui_status_t status;
};

static struct gui_object_t gui;

static int _utils_gui_init_event_buffer(size_t size);
static void _utils_gui_free_event_buffer();
static void _utils_gui_event_buffer_write(struct gui_event_handler_t handler);

static void _utils_gui_register_event_handler(SDL_EventType event, event_callback_t callback);
static void _utils_gui_callback_quit(SDL_Event* event);
static void _utils_gui_callback_keydown(SDL_Event* event);
static void _utils_gui_process_event(SDL_Event* event);

enum gui_err_t utils_gui_init(int window_width, int window_height)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        utils_log(LOG_LEVEL_ERR, "error initializing SDL: %s", SDL_GetError());
        return GUI_ERR_INIT_ERR;
    }

    if(SDL_CreateWindowAndRenderer(
        window_width,
        window_height,
        0,
        &gui.window,
        &gui.renderer
    ) != 0) {
        utils_log(LOG_LEVEL_ERR, "error initializing SDL window/renderer: %s", SDL_GetError());
        return GUI_ERR_INIT_ERR;
    }

    // REVIEW
    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "1");

    gui.window_height = window_height;
    gui.window_width = window_width;
    gui.origin = GUI_ORIGIN_DEFAULT;
    gui.graph = NULL;
    gui.status = GUI_STATUS_CONTINUE;

    _utils_gui_init_event_buffer(GUI_EVENT_HANDLER_BUFFER_SIZE);

    _utils_gui_register_event_handler(SDL_QUIT, _utils_gui_callback_quit);
    _utils_gui_register_event_handler(SDL_KEYDOWN, _utils_gui_callback_keydown);

    return GUI_ERR_SUCCESS;
}

void utils_gui_set_coord_origin(int origin_x, int origin_y)
{
    gui.origin.x = origin_x;
    gui.origin.y = origin_y;
}

void utils_gui_clear_render(struct rgba_t color)
{
    SDL_SetRenderDrawColor(
        gui.renderer, 
        color.r, 
        color.g, 
        color.b, 
        color.a
    );
    SDL_RenderClear(gui.renderer);
}

enum gui_err_t utils_gui_render_coord_axes(struct rgba_t color)
{
    SDL_SetRenderDrawColor(
        gui.renderer, 
        color.r, 
        color.g, 
        color.b, 
        color.a
    );

    // vertical axis
    SDL_RenderDrawLine(gui.renderer, gui.origin.x, 0, gui.origin.x, gui.window_height);

    // horizontal axis
    SDL_RenderDrawLine(gui.renderer, 0, gui.origin.y, gui.window_width, gui.origin.y);

    return GUI_ERR_SUCCESS;
}

// FIXME динамическое масштабирование
enum gui_err_t utils_gui_render_graph(struct rgba_t color, double coeff_a, double coeff_b, double coeff_c)
{
    utils_assert(utils_isfinite(coeff_a));
    utils_assert(utils_isfinite(coeff_b));
    utils_assert(utils_isfinite(coeff_c));
    
    if(gui.graph == NULL) {
        gui.graph = (SDL_Point*)calloc(GUI_PLOT_POINTS_NUM, sizeof(SDL_Point));
        if(gui.graph == NULL) {
            utils_log(
                LOG_LEVEL_ERR, 
                "failed to allocate %lu bytes "
                "for point buffer",
                GUI_PLOT_POINTS_NUM * sizeof(SDL_Point)
            );
            return GUI_ERR_MEM_ALLOC_ERR;
        }
    }

    SDL_SetRenderDrawColor(
        gui.renderer, 
        color.r, 
        color.g, 
        color.b, 
        color.a
    );

    SDL_Point point = {0, 0};
    for(int i = 0; i < GUI_PLOT_POINTS_NUM; ++i) {
        float scale = (float)(gui.window_width) / (float)(GUI_PLOT_POINTS_NUM);
        point.x = (int)((float)i * scale);
        int x_centered = - gui.origin.x + point.x;

        point.y = 
              gui.origin.y 
            - (int)(coeff_a * x_centered * x_centered + coeff_b * x_centered + coeff_c);

        gui.graph[i] = point;
    }

    SDL_RenderDrawLines(gui.renderer, gui.graph, GUI_PLOT_POINTS_NUM);

    return GUI_ERR_SUCCESS;
}

void utils_gui_show()
{
    SDL_RenderPresent(gui.renderer);
}

// FIXME перемещение по клавишам
enum gui_status_t utils_gui_event_loop()
{
    static SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
        _utils_gui_process_event(&event);

    return gui.status;
}

void utils_gui_end()
{
    _utils_gui_free_event_buffer();

    free(gui.graph);

    SDL_DestroyRenderer(gui.renderer);
    SDL_DestroyWindow(gui.window);
    SDL_Quit();
}

int _utils_gui_init_event_buffer(size_t size)
{
    gui.event_handlers.buffer = 
        (struct gui_event_handler_t*)calloc(size, sizeof(struct gui_event_handler_t));

    if(gui.event_handlers.buffer == NULL) {
        utils_log(
            LOG_LEVEL_ERR,
            "failed to allocate %lu bytes "
            "for event handlers buffer",
            size * sizeof(struct gui_event_handler_t)
        );
        return 1;
    }

    gui.event_handlers.rd_ptr = gui.event_handlers.buffer;
    gui.event_handlers.wr_ptr = gui.event_handlers.buffer;

    gui.event_handlers.size = size;

    return 0;
}

void _utils_gui_free_event_buffer()
{
    utils_assert(gui.event_handlers.buffer != NULL);

    free(gui.event_handlers.buffer);
    gui.event_handlers.rd_ptr = NULL;
    gui.event_handlers.wr_ptr = NULL;
}

void _utils_gui_event_buffer_write(struct gui_event_handler_t handler)
{
    utils_assert(gui.event_handlers.buffer != NULL);

    *gui.event_handlers.wr_ptr = handler;

    if((size_t)(gui.event_handlers.wr_ptr - gui.event_handlers.buffer)
        >= gui.event_handlers.size)
        gui.event_handlers.wr_ptr = gui.event_handlers.buffer;
    else 
        ++gui.event_handlers.wr_ptr;
}

void _utils_gui_register_event_handler(SDL_EventType event, event_callback_t callback)
{
    utils_assert(callback != NULL);

    struct gui_event_handler_t handler = {.event_type = event, .callback = callback};

    _utils_gui_event_buffer_write(handler);
}

void _utils_gui_callback_quit(SDL_Event *event)
{
    EXPR_UNUSED(event);
    utils_log(LOG_LEVEL_DEBUG, "[event] quit");
    gui.status = GUI_STATUS_QUIT;
}

void _utils_gui_callback_keydown(SDL_Event* event)
{
    utils_log(LOG_LEVEL_DEBUG, "[event] key pressed");

    switch(event->key.keysym.sym)
    {
        case SDLK_UP:
            gui.origin.y -= GUI_ORIGIN_MOVE_DELTA;
            break;
        case SDLK_DOWN:
            gui.origin.y += GUI_ORIGIN_MOVE_DELTA;
            break;
        case SDLK_LEFT:
            gui.origin.x -= GUI_ORIGIN_MOVE_DELTA;
            break;
        case SDLK_RIGHT:
            gui.origin.x += GUI_ORIGIN_MOVE_DELTA;
            break;
        default:
            break;
    }
}


void _utils_gui_process_event(SDL_Event* event)
{
    for(size_t i = 0; i < gui.event_handlers.size; ++i)
        if(gui.event_handlers.buffer[i].event_type == event->type) {
            gui.event_handlers.buffer[i].callback(event);
            break;
        }
}
