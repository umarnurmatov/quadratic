#include <stdlib.h>
#include <stdio.h>

#include "logutils.h"
#include "quadratic.h"
#include "ioutils.h"
#include "colorutils.h"
#include "guiutils.h"

static const char* LOG_FILENAME = "log.txt";
static const char* LOG_PATH = "log";

static const int GUI_WINDOW_WIDTH = 1000;
static const int GUI_WINDOW_HEIGHT = 800;

// FIXME добавить argc argv
int main()
{
    if(utils_init_log(LOG_FILENAME, LOG_PATH) != LOG_INIT_SUCCESS)
        return 1;

    if(utils_gui_init(GUI_WINDOW_WIDTH, GUI_WINDOW_HEIGHT) != GUI_ERR_SUCCESS)
        return 1;
    utils_gui_set_coord_origin(GUI_WINDOW_WIDTH / 2, GUI_WINDOW_HEIGHT / 2);

    utils_colored_fprintf(
        stdout, 
        ANSI_COLOR_BOLD_GREEN, 
        "#######################################################\n"
        "### This is program for solving quadratic equations ###\n"
        "###         © Nurmatov Umar aka n1njaeng1neer, 2025 ###\n"
        "#######################################################\n"
    );

    double coeff_a = 0.0, coeff_b = 0.0, coeff_c = 0.0; // coefficients
    double root_a = 0.0, root_b = 0.0;                  // roots

    utils_colored_fprintf(
        stdout,
        ANSI_COLOR_BOLD_BLUE,
        "Input equation coefficients [ax² + bx + c = 0]:\n"
    );

    utils_colored_fprintf(stdout, ANSI_COLOR_BOLD_WHITE, "\tinput coeff [a]: ");
    if(input_double_until_correct(&coeff_a) == INPUT_ERR_EOF_REACHED) return 1;

    utils_colored_fprintf(stdout, ANSI_COLOR_BOLD_WHITE, "\tinput coeff [b]: ");
    if(input_double_until_correct(&coeff_b) == INPUT_ERR_EOF_REACHED) return 1;

    utils_colored_fprintf(stdout, ANSI_COLOR_BOLD_WHITE, "\tinput coeff [c]: ");
    if(input_double_until_correct(&coeff_c) == INPUT_ERR_EOF_REACHED) return 1;

    enum root_cnt_t root_cnt = solve_quadratic_equation(coeff_a, coeff_b, coeff_c, &root_a, &root_b);
    print_quadratic_equation_solution(root_cnt, root_a, root_b, ANSI_COLOR_BOLD_BLUE);

    if(utils_is_option_set(options_mask, OPTION_GRAPHIC)) {
        if(utils_gui_init(GUI_WINDOW_WIDTH, GUI_WINDOW_HEIGHT) != GUI_ERR_SUCCESS)
            return 1;
        utils_gui_set_coord_origin(GUI_WINDOW_WIDTH / 2, GUI_WINDOW_HEIGHT / 2);
    
        while(utils_gui_event_loop() == GUI_STATUS_CONTINUE) {
        utils_gui_clear_render(GUI_COLOR_BLACK);

        if(utils_gui_render_coord_axes(GUI_COLOR_WHITE) != GUI_ERR_SUCCESS)
            return 1;

        if(utils_gui_render_graph(
            GUI_COLOR_GREEN, coeff_a, coeff_b, coeff_c) != GUI_ERR_SUCCESS)
            return 1;

        utils_gui_show();
    }

    utils_gui_end();
    }

    utils_end_log(); // FIXME atexit возможно

    return 0;
}