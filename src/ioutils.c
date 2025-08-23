#include "ioutils.h"

void clear_stdin_buffer()
{
    int buffered_char;
    do {
        buffered_char = getchar();
    } while((buffered_char != '\n') && (buffered_char != EOF));
}

enum input_err_t input_double(double *d)
{
    int assigned = scanf(" %lf", d);
    clear_stdin_buffer();
    switch (assigned)
    {
        case -1:
            return INPUT_ERR_EOF_REACHED;
            break;
        case 1:
            return INPUT_ERR_ASSIGMENT_SUCCESS;
            break;
        default:
            return INPUT_ERR_ASSIGMENT_FAIL;
            break;
    }
}

enum input_err_t input_double_until_correct(double *d)
{
    enum input_err_t errcode = INPUT_ERR_NONE;
    do {
        errcode = input_double(d);
        if(errcode == INPUT_ERR_EOF_REACHED) {
            fprintf(stderr, "\n\tEOF reached, exiting.\n");
            break;
        }
        else if(errcode == INPUT_ERR_ASSIGMENT_FAIL) {
            fprintf(stderr, "\tEnter a valid numeric value.\n\t");
        }
    } while(errcode != INPUT_ERR_ASSIGMENT_SUCCESS);
    return errcode;
}

void print_quadratic_equation_solution(enum root_cnt_t root_cnt, double root_a, double root_b)
{
    switch(root_cnt) {
        case ROOT_CNT_NO_ROOTS:
            printf("Equation has no solution\n");
            break;
        case ROOT_CNT_1:
            printf("Equation has 1 root: %lf\n", root_a);
            break;
        case ROOT_CNT_2:
            printf("Equation has 2 roots: %lf and %lf\n", root_a, root_b);
            break;
        case ROOT_CNT_INF:
            printf("Equation is non-quadratic and contains infinite solutions\n");
            break;
        case ROOT_CNT_LINEAR_EQ:
            printf("Equation is linear. This program is not intended for solving linear equations.\n");
            break;
        default:
            break;
    }
}