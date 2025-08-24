#include "quadratic.h"
#include "ioutils.h"

int main()
{
    double coeff_a = 0.0, coeff_b = 0.0, coeff_c = 0.0;
    double root_a = 0.0, root_b = 0.0;
    enum root_cnt_t root_cnt;
    for(int i = 0; i < 10; ++i) {
        coeff_a = rand();
        coeff_b = rand();
        coeff_c = rand();

        utils_colored_fprintf(stdout, ANSI_COLOR_BOLD_BLUE, "Testing with coefficients: %lf %lf %lf\n", coeff_a, coeff_b, coeff_c);
        root_cnt = solve_quadratic_equation(coeff_a, coeff_b, coeff_c, &root_a, &root_b);
        print_quadratic_equation_solution(root_cnt, root_a, root_b);
        puts("##########\n");
    }
    return 0;
}
