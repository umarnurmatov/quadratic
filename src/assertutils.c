#include "assertutils.h"

void utils_assert_fail(const char* expression, const char* filename, int linenumber)
{
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_WHITE, "%s:%d: assertion failed\n", filename, linenumber);
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_RED, "   assert(%s)\n", expression);
    abort();
}