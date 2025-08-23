#include "colorutils.h"

void utils_fprintf_with_mode(FILE *stream, const char *mode, const char *fmtstring, ...)
{
    fprintf(stream, mode);
    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    vfprintf(stream, fmtstring, va_arg_list);
    va_end(va_arg_list);
    fprintf(stream, ANSI_COLOR_RESET);
}
