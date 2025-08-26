#include <SDL2/SDL.h>

#include "guiutils.h"
#include "logutils.h"
#include "assertutils.h"

static const char* GUI_WINDOW_NAME = "Quadratic Solver GUI";
static const int GUI_PLOT_POINTS_NUM = 1000;

struct gui_object_t
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    int window_height;
    int window_width;
};

static struct gui_object_t gui_obj;

int utils_init_gui(int window_width, int window_height)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        utils_log(LOG_LEVEL_ERR, "error initializing SDL: %s", SDL_GetError());
        return 1;
    }

    if(SDL_CreateWindowAndRenderer(
        window_width,
        window_height,
        0,
        &gui_obj.window,
        &gui_obj.renderer
    ) != 0) {
        utils_log(LOG_LEVEL_ERR, "error initializing SDL window/renderer: %s", SDL_GetError());
        return 1;
    }

    gui_obj.window_height = window_height;
    gui_obj.window_width = window_width;

    return 0;
}

void utils_show_equation_gui(double coeff_a, double coeff_b, double coeff_c)
{
    utils_assert(!isnan(coeff_a) && isfinite(coeff_a));
    utils_assert(!isnan(coeff_b) && isfinite(coeff_b));
    utils_assert(!isnan(coeff_c) && isfinite(coeff_c));

    SDL_SetRenderDrawColor(gui_obj.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gui_obj.renderer);

    SDL_SetRenderDrawColor(gui_obj.renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_Point* points = (SDL_Point*)calloc(GUI_PLOT_POINTS_NUM, sizeof(SDL_Point));
    for(int i = 0; i < GUI_PLOT_POINTS_NUM; ++i) {
        SDL_Point pt;
        pt.x = i * (gui_obj.window_width / GUI_PLOT_POINTS_NUM);
        pt.y = gui_obj.window_height - coeff_a * i * i + coeff_b * i + coeff_c;
        points[i] = pt;
    }

    SDL_RenderDrawLines(gui_obj.renderer, points, GUI_PLOT_POINTS_NUM);

    SDL_RenderPresent(gui_obj.renderer);
}

int utils_render_loop_gui()
{
    SDL_PollEvent(&gui_obj.event);
    if(gui_obj.event.type == SDL_QUIT)
        return 1;
    return 0;
}

void utils_end_gui()
{
    SDL_DestroyRenderer(gui_obj.renderer);
    SDL_DestroyWindow(gui_obj.window);
    SDL_Quit();
}