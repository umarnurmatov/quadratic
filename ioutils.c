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

int input_double_until_correct(double *d)
{
    enum input_err_t errcode = INPUT_ERR_NONE;
    do {
        errcode = input_double(d);
        if(errcode == INPUT_ERR_EOF_REACHED) {
            fprintf(stderr, "\n\tEOF reached, exiting.\n");
            return 1;
        }
        else if(errcode == INPUT_ERR_ASSIGMENT_SUCCESS) {
            fprintf(stderr, "\tEnter a valid numeric value.\n\t");
        }
    } while(errcode != INPUT_ERR_ASSIGMENT_SUCCESS);
    return 0;
}