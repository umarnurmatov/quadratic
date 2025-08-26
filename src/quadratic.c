#include "quadratic.h"

enum root_cnt_t solve_quadratic_equation(double coeff_a, double coeff_b, double coeff_c, double *root_a, double *root_b)
{
    assert(!isnan(coeff_a) && !isinf(coeff_a));
    assert(!isnan(coeff_b) && !isinf(coeff_b));
    assert(!isnan(coeff_c) && !isinf(coeff_c));

    if(utils_equal_zero(coeff_a)) {
        if(utils_equal_zero(coeff_b)) {
            if(utils_equal_zero(coeff_c)) {
                *root_a = INFINITY; 
                return ROOT_CNT_INF;
            }
            else {
                *root_a = *root_b = NAN;
                return ROOT_CNT_NO_ROOTS;
            }
        }
        else {
            *root_a = *root_b = NAN;
            return ROOT_CNT_LINEAR_EQ;
        }
    }
    else {
        double discriminant = coeff_b * coeff_b - 4.0 * coeff_a * coeff_c;
        if(utils_equal_zero(discriminant)) {
            *root_a = *root_b = -coeff_b / ( 2 * coeff_a );
            return ROOT_CNT_1;
        }
        else if (utils_gt_zero(discriminant)) {
            double sqrt_discriminant = sqrt(discriminant);
            *root_a = ( -coeff_b + sqrt_discriminant ) / ( 2 * coeff_a ); 
            *root_b = ( -coeff_b - sqrt_discriminant ) / ( 2 * coeff_a ); 
            return ROOT_CNT_2;
        }
        else {
            *root_a = *root_b = NAN;
            return ROOT_CNT_NO_ROOTS;
        }
    }
}
