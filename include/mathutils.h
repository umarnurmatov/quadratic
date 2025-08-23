#pragma once

#include <math.h>

static const double EPSILON = 1e-10;
static const double ZERO = 0.0;

/// @brief compares two floating-point variables on equality with precision
/// @param a pointer to first variable
/// @param b pointer to second variable
/// @return 1 if variables are equal, 0 otherwise
int equal_with_precision(double a, double b);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value equals zero, 0 otherwise
int equal_zero(double a);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value greater than zero, 0 otherwise
int gt_zero(double a);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value less than zero, 0 otherwise
int lt_zero(double a);

