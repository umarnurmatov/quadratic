#pragma once
#include <stdlib.h>
#include <stdio.h>

/// @brief input error types
enum input_err_t
{
    INPUT_ERR_NONE,
    INPUT_ERR_EOF_REACHED,
    INPUT_ERR_ASSIGMENT_FAIL,
    INPUT_ERR_ASSIGMENT_SUCCESS
};

/// @brief clears stdin buffer until reaches \\n or EOF
void clear_stdin_buffer();

/// @brief validated input of floating-point numeric value
/// @param d pointer to variable where inputed value will be stored
/// @return see input_err_t for explanations
enum input_err_t input_double(double *d);

/// @brief validated input of floating-point numeric value until correct value entered
/// @param d pointer to variable where inputed value will be stored
/// @return 1 if EOF occured in stdin, 0 otherwise
int input_double_until_correct(double *d);

