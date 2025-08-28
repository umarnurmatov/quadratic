#include "optutils.h"

#include "assertutils.h"
#include "utils.h"
#include "logutils.h"

enum opt_err_t utils_get_options(int argc, char* argv[], 
    const struct option* long_options, opt_t* options_mask)
{
    utils_assert(long_options != NULL);
    utils_assert(options_mask != NULL);

    while(1) {
        int option_val = getopt_long(argc, argv, "", long_options, NULL);

        if(option_val == -1)
            break;

        if((size_t)(option_val) >= (size_t)(BYTE) * sizeof(opt_t)) {
            utils_log(
                LOG_LEVEL_ERR, 
                "option [value %d] doesn't fit to mask "
                "(mask size: %lu bytes)",
                option_val,
                sizeof(opt_t)
            );
            return OPTION_ERR_ERROR;
        }

        opt_t option_bit_mask = (opt_t)(1 << option_val);
        *options_mask |= option_bit_mask;
    }

    return OPTION_ERR_SUCCESS;
}

int utils_is_option_set(opt_t options_mask, opt_t option)
{
    return options_mask & option;
}
