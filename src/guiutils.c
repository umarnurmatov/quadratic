#include "guiutils.h"

#include <SDL2/SDL.h>

#include "logutils.h"
#include "assertutils.h"
#include "floatutils.h"

static const int GUI_PLOT_POINTS_NUM = 1000;
static const SDL_Point GUI_ORIGIN_DEFAULT = {0, 0};

struct gui_object_t
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    SDL_Point* graph;
    SDL_Point origin;
    int window_height;
    int window_width;
};

static struct gui_object_t gui;

enum gui_err_t utils_gui_init(int window_width, int window_height)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
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

    gui.window_height = window_height;
    gui.window_width = window_width;
    gui.origin = GUI_ORIGIN_DEFAULT;
    gui.graph = NULL;

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
        point.x = i * (gui.window_width / GUI_PLOT_POINTS_NUM);
        int x_centered = - gui.origin.x + point.x;

        point.y = 
              gui.window_height 
            - gui.origin.y 
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
enum gui_status_t utils_gui_render_loop()
{
    SDL_PollEvent(&gui.event);
    if(gui.event.type == SDL_QUIT)
        return GUI_STATUS_QUIT;
    return GUI_STATUS_CONTINUE;
}

void utils_gui_end()
{
    free(gui.graph);
    SDL_DestroyRenderer(gui.renderer);
    SDL_DestroyWindow(gui.window);
    SDL_Quit();
}