#include <unistd.h>
#include <stdlib.h>
#include <threads.h>

#include "quadratic.h"
#include "ioutils.h"
#include "colorutils.h"
#include "floatutils.h"
#include "logutils.h"

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
static const char* LOG_FILENAME = "log.txt";
static const char* LOG_PATH = "log";

static const int TEST_THREAD_NUM = 3;

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

struct test_thrd_data_t
{
    const char* input_filename;
    enum test_err_t test_err;
};

int all_test(struct test_thrd_data_t* test_thrd_data);
enum test_err_t one_test(struct test_data_t* test_data);
enum test_err_t read_one_test(char* filebuffer, struct test_data_t* test_data, int* bytes_read);
int utils_equal_with_precision_nan_inf(double a, double b);

int main()
{
    utils_init_log(LOG_FILENAME, LOG_PATH);
    thrd_t threads[TEST_THREAD_NUM];
    struct test_thrd_data_t test_data[TEST_THREAD_NUM];

    for(int i = 0; i < TEST_THREAD_NUM; ++i) {
        test_data[i].input_filename = TEST_INPUT_RELATIVE_FILEPATH;
        thrd_create(&threads[i], (thrd_start_t)all_test, &test_data[i]);
    }

    for(int i = 0; i < TEST_THREAD_NUM; ++i) {
        int thrd_res;
        thrd_join(threads[i], &thrd_res);
    }
    utils_end_log();

    return 0;
}

int all_test(struct test_thrd_data_t* test_thrd_data)
{
    utils_assert(test_thrd_data->input_filename != NULL);

    utils_log(LOG_LEVEL_INFO, "Running tests");

    char* test_file_realpath = realpath(test_thrd_data->input_filename, NULL);
    FILE* test_file = open_file(test_file_realpath, "r");
    if(test_file == NULL) {
        test_thrd_data->test_err = TEST_ERR_FILE_OPEN_ERR;
        return 0;
    }
    free(test_file_realpath);

    char* test_file_buf = bufferize_file(test_file);
    size_t test_file_size = get_file_size(test_file);
    
    char* test_file_buf_ptr = test_file_buf;
    int bytes_read = 0;
    int test_cnt = 0;
    struct test_data_t test_data;
    while(test_file_buf_ptr - test_file_buf < (long)test_file_size) {
        if(read_one_test(test_file_buf_ptr, &test_data, &bytes_read) == TEST_ERR_FILE_READ_ERR) {
            test_thrd_data->test_err = TEST_ERR_FILE_READ_ERR;
            return 0;
        }
        if(one_test(&test_data) == TEST_ERR_TEST_FAIL) {
            test_thrd_data->test_err = TEST_ERR_TEST_FAIL;
            return 0;
        }
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

    return 0;
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
        &test_data->root_a,
        &test_data->root_b,
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


// FIXME обернуть стандартные мьютексы в макросы чтобы они разворачивались в 0 при однопотоке