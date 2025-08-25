#include "quadratic.h"
#include "ioutils.h"

static const size_t TEST_DATA_NUM_FIELDS = 5;
/*
Every single test is written in one line.
Single test is structured as followed:
1. No roots:  <c1> <c2> <c3> nan  nan
2. 1 root:    <c1> <c2> <c3> <r1> nan
3. 2 roots:   <c1> <c2> <c3> <r1> <r2>
4. inf roots: <c1> <c2> <c3> inf  <any>
5. linear:    <c1> <c2> <c3> nan  nan (yeah, we don't solve linear eq)
*/
static const char* TEST_INPUT_RELATIVE_FILEPATH = "test/input.txt";

struct test_data_t
{
    double coeff_a;
    double coeff_b;
    double coeff_c;
    double root_a;
    double root_b;
};

enum test_err_t
{
    TEST_ERR_TEST_SUCCESS,
    TEST_ERR_TEST_FAIL,
    TEST_ERR_FILE_OPEN_ERR,
    TEST_ERR_FILE_READ_ERR,
    TEST_ERR_FILE_READ_SUCCESS
};

enum test_err_t all_test(const char* test_input_filename);
enum test_err_t one_test(struct test_data_t* test_data);
enum test_err_t read_one_test(char* filebuffer, struct test_data_t* test_data, int* bytes_read);
int utils_equal_with_precision_nan_inf(double a, double b);

int main()
{
    enum test_err_t test_err = all_test(TEST_INPUT_RELATIVE_FILEPATH);

    switch(test_err) {
        case TEST_ERR_TEST_FAIL:
        case TEST_ERR_FILE_OPEN_ERR:
        case TEST_ERR_FILE_READ_ERR:
            return 1;
            break;
        case TEST_ERR_TEST_SUCCESS:
        case TEST_ERR_FILE_READ_SUCCESS:
            break;
        default:
            break;
    }

    return 0;
}

enum test_err_t all_test(const char* test_input_filename)
{
    utils_assert(test_input_filename != NULL);

    char* test_file_realpath = realpath(test_input_filename, NULL);
    FILE* test_file = open_file(test_file_realpath, "r");
    if(test_file == NULL)
        return TEST_ERR_FILE_OPEN_ERR;
    free(test_file_realpath);

    char* test_file_buf = bufferize_file(test_file);
    size_t test_file_size = get_file_size(test_file);
    
    char* test_file_buf_ptr = test_file_buf;
    int bytes_read = 0;
    int test_cnt = 0;
    struct test_data_t test_data;
    while(test_file_buf_ptr - test_file_buf < (long)test_file_size) {
        if(read_one_test(test_file_buf_ptr, &test_data, &bytes_read) == TEST_ERR_FILE_READ_ERR)
            return TEST_ERR_FILE_READ_ERR; 
        if(one_test(&test_data) == TEST_ERR_TEST_FAIL)
            return TEST_ERR_TEST_FAIL;
        test_file_buf_ptr += bytes_read;
        ++test_cnt;
    }

    utils_colored_fprintf(
        stdout, 
        ANSI_COLOR_BOLD_GREEN, 
        "%d test%c passed successfully\n", 
        test_cnt,
        test_cnt == 1 ? ' ' : 's'
    );

    fclose(test_file);
    free(test_file_buf);

    return TEST_ERR_TEST_SUCCESS;
}

enum test_err_t one_test(struct test_data_t* test_data)
{
    utils_assert(test_data != NULL);

    double root_a_test = 0.0, root_b_test = 0.0;
    
    solve_quadratic_equation(
        test_data->coeff_a, 
        test_data->coeff_b, 
        test_data->coeff_c, 
        &root_a_test, 
        &root_b_test
    );
    
    if(!utils_equal_with_precision_nan_inf(test_data->root_a, root_a_test) || 
    !utils_equal_with_precision_nan_inf(test_data->root_b, root_b_test)) {
        utils_colored_fprintf(
            stderr, 
            ANSI_COLOR_BOLD_RED, 
            "Test failed. Expected: %lf, %lf, actual: %lf, %lf\n",
            test_data->root_a,
            test_data->root_b,
            root_a_test,
            root_b_test
        );
        return TEST_ERR_TEST_FAIL;
    }
    
    return TEST_ERR_TEST_SUCCESS;
}

enum test_err_t read_one_test(char* filebuffer, struct test_data_t* test_data, int* bytes_read)
{
    utils_assert(filebuffer != NULL);
    utils_assert(test_data != NULL);
    utils_assert(bytes_read != NULL);
    
    int assigned = sscanf(filebuffer, "%lf %lf %lf %lf %lf%n", 
        &test_data->coeff_a, 
        &test_data->coeff_b, 
        &test_data->coeff_c,
        &test_data->root_b,
        &test_data->root_a,
        bytes_read
    );

    if(assigned != TEST_DATA_NUM_FIELDS)
        return TEST_ERR_FILE_READ_ERR;

    return TEST_ERR_FILE_READ_SUCCESS;
}

int utils_equal_with_precision_nan_inf(double a, double b)
{
    if(utils_isnan(a) && utils_isnan(b)) return 1;
    else if(utils_isinf(a) && utils_isinf(b)) return 1;
    else if(utils_equal_with_precision(a, b)) return 1;
    return 0;
}

// FIXME почему везде используетсяя FILE* а не FILE
// FIXME что происходит до main и после него
// FIXME doxygen
// FIXME README 

