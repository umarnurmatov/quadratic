#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/// @brief converts double to integer bit-by-bit
/// @param x variable to convert
/// @return bit-by-bit converted x
uint64_t utils_double_to_integer(double x);

/// @brief extracts exponent from double-precision floating-point variable
/// @param x double-precision floating-point variable
/// @return exponent of x 
uint16_t utils_get_double_exponent(double x);

/// @brief extracts fraction from double-precision floating-point variable
/// @param x double-precision floating-point variable
/// @return fraction of x 
uint64_t utils_get_double_fraction(double x);

/// @brief checks if double-precision floating-point variable is NaN
/// @param x variable to check
/// @return 1 if x is None, 0 otherwise
int utils_isnan(double x);

/// @brief checks if double-precision floating-point variable is +/- infinity
/// @param x variable to check
/// @return 1 if x is +/- infinity, 0 otherwise
int utils_isinf(double x);

/// @brief checks if double-precision floating-point variable is finite
/// @param x variable to check
/// @return 1 if x is finite, 0 otherwise
int utils_isfinite(double x);