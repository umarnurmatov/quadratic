#include "colorutils.h"

void utils_fprintf_with_mode(FILE *stream, const char *mode, const char *fmtstring, ...)
{
    utils_assert(stream != NULL);
    utils_assert(mode != NULL);
    utils_assert(fmtstring != NULL);

    fputs(stream, mode);

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    vfprintf(stream, fmtstring, va_arg_list);
    va_end(va_arg_list);

    fputs(stream, ANSI_COLOR_RESET);
}
