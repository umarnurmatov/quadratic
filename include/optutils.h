#pragma once

#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>

/// @brief option bitmask type
typedef uint8_t opt_t;

/// @brief option util funcs error
enum opt_err_t
{
    OPTION_ERR_ERROR,
    OPTION_ERR_SUCCESS
};

/// @brief extracts long options to bitmask
/// @param argc argument count
/// @param argv argumets 
/// @param long_options user-defined long (i.e. consistinig of more
///                     than one character) options
/// @param options_mask options bitmask
/// @return see opt_err_t 
enum opt_err_t utils_get_options(int argc, char* argv[], 
    const struct option* long_options, opt_t* options_mask);

/// @brief checks if \ref option is set
/// @param options_mask options bitmask 
/// @param option option to check 
/// @return 1 if option is set, 0 otherwise 
int utils_is_option_set(opt_t options_mask, opt_t option);
