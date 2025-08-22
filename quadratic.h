#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>

#include "mathutils.h"

/// @brief quadratic equation's root count
enum root_cnt_t
{
    ROOT_CNT_NO_ROOTS,
    ROOT_CNT_1,
    ROOT_CNT_2,
    ROOT_CNT_INF,
    ROOT_CNT_LINEAR_EQ
};

/// @brief solves quadratic equation
/// @param [in] coeff_a pointer to variable with coefficient a
/// @param [in] coeff_b pointer to variable with coefficient b
/// @param [in] coeff_c pointer to variable with coefficient c
/// @param [out] root_a first equation root 
/// @param [out] root_b second equation root
/// @return see root_cnt_t for explanations
enum root_cnt_t solve_quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_a, double *root_b);

/// @brief processes and prints quadratic equation solutions  
/// @param root_cnt see root_cnt_t for explanations
/// @param root_a first root
/// @param root_b second root
void print_quadratic_equation_solution(enum root_cnt_t root_cnt, double root_a, double root_b);
