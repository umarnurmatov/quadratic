#pragma once

#include <stdio.h>

#include "quadratic.h"

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
enum input_err_t input_double_until_correct(double *d);

/// @brief open file
/// @param filename filename
/// @param modes file open modes
/// @return pointer to filestream if file opened successfully, NULL otherwise
FILE* open_file(const char *filename, const char *modes);

/// @brief creates directory
/// @param path full path
/// @return 0 if dir created successfully, 1 otherwise
int create_dir(const char* path);

/// @brief returns string containing cwd path, buffer is allocated internally
/// @return pointer to string buffer on success, NULL otherwise 
char* get_current_working_dir();

/// @brief get file size in bytes
/// @param file filestream
/// @return file size in bytes 
size_t get_file_size(FILE* file);

/// @brief reads file to buffer and returns pointer to that buffer
/// @param file file to bufferize
/// @return pointer to buffer 
char* bufferize_file(FILE* file);

/// @brief processes and prints quadratic equation solutions  
/// @param root_cnt see root_cnt_t for explanations
/// @param root_a first root
/// @param root_b second root
void print_quadratic_equation_solution(enum root_cnt_t root_cnt, double root_a, double root_b);
