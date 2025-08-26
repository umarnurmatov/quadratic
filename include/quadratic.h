#pragma once

/// @brief quadratic equation's root count
enum root_cnt_t
{
    ROOT_CNT_NONE,
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
/// @return see root_cnt_t                                                   \n 
///         ROOT_CNT_NO_ROOTS:  root_a = NaN,          root_b = NaN          \n 
///         ROOT_CNT_1:         root_a = NaN,          root_b = any value    \n 
///         ROOT_CNT_2:         root_a = finite value, root_b = finite value \n 
///         ROOT_CNT_INF:       root_a = inf,          root_b = any value    \n 
///         ROOT_CNT_LINEAR_EQ: root_a = NaN,          root_b = NaN          \n 
enum root_cnt_t solve_quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_a, double *root_b);
