#include <stdlib.h>
#include <stdio.h>

#include "quadratic.h"
#include "ioutils.h"

int main()
{
    printf("#######################################################\n");
    printf("### This is program for solving quadratic equations ###\n");
    printf("###         © Nurmatov Umar aka n1njaeng1neer, 2025 ###\n");
    printf("#######################################################\n");

    double coeff_a = 0.0, coeff_b = 0.0, coeff_c = 0.0; // coefficients
    double root_a = 0.0, root_b = 0.0;                  // roots

    printf("Input equation coefficients [ax² + bx + c = 0]:\n");

    printf("\tinput coeff [a]: ");
    if(input_double_until_correct(&coeff_a) == INPUT_ERR_EOF_REACHED) return 1;
    printf("\tinput coeff [b]: ");
    if(input_double_until_correct(&coeff_b) == INPUT_ERR_EOF_REACHED) return 1;
    printf("\tinput coeff [c]: ");
    if(input_double_until_correct(&coeff_c) == INPUT_ERR_EOF_REACHED) return 1;

    enum root_cnt_t root_cnt = solve_quadratic_equation(coeff_a, coeff_b, coeff_c, &root_a, &root_b);
    print_quadratic_equation_solution(root_cnt, root_a, root_b);

    return 0;
}