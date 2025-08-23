#include "quadratic.h"

enum root_cnt_t solve_quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_a, double *root_b)
{
    assert(!isnan(coeff_a) && !isinf(coeff_a));
    assert(!isnan(coeff_b) && !isinf(coeff_b));
    assert(!isnan(coeff_c) && !isinf(coeff_c));

    if(equal_zero(coeff_a)) {
        if(equal_zero(coeff_b))
            return equal_zero(coeff_c) ? ROOT_CNT_INF : ROOT_CNT_NO_ROOTS;
        else 
            return ROOT_CNT_LINEAR_EQ;
    }
    else {
        double discriminant = coeff_b * coeff_b - 4.0 * coeff_a * coeff_c;
        if(equal_zero(discriminant)) {
            *root_a = *root_b = -coeff_b / ( 2 * coeff_a );
            return ROOT_CNT_1;
        }
        else if (gt_zero(discriminant)) {
            *root_a = ( -coeff_b + sqrt(discriminant) ) / ( 2 * coeff_a ); 
            *root_b = ( -coeff_b - sqrt(discriminant) ) / ( 2 * coeff_a ); 
            return ROOT_CNT_2;
        }
        else {
            return ROOT_CNT_NO_ROOTS;
        }
    }
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