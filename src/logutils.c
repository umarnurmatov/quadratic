#include "logutils.h"

static const char* LOG_RELATIVE_FILEPATH = "log/log.txt";
static FILE* log_stream = NULL;
static enum log_level_t log_level_glob = LOG_LEVEL_DEBUG;
static const int MAX_TIME_STR_LEN = 70;

// FIXME Pass filename
void utils_init_log(void)
{
    char* full_path = realpath(LOG_RELATIVE_FILEPATH, NULL);
    log_stream = open_file(full_path, "w");
    free(full_path);

    if(log_stream == NULL) 
        log_stream = stderr;
}

void utils_end_log(void)
{
    utils_assert(log_stream != NULL);

    int is_console = isatty(fileno(log_stream));
    if(!is_console) fclose(log_stream);
}

void utils_set_global_log_level(enum log_level_t _log_level_glob)
{
    log_level_glob = _log_level_glob;
}

const char* utils_get_log_level_str(enum log_level_t log_level)
{
    switch(log_level) {
        case LOG_LEVEL_ERR:
            return "ERROR";
            break;
        case LOG_LEVEL_WARN:
            return "WARN";
            break;
        case LOG_LEVEL_INFO:
            return "INFO";
            break;
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
            break;
        default:
            return "";
            break;
    }
}

void utils_log(enum log_level_t log_level, const char *fmtstring, ...)
{
    if(log_level > log_level_glob)
        return;

    utils_assert(log_stream != NULL);

    const char* log_level_str = utils_get_log_level_str(log_level);
    time_t cur_time = time(NULL);
    struct tm* iso_time = localtime(&cur_time);
    char time_buff[MAX_TIME_STR_LEN];
    strftime(time_buff, sizeof(time_buff), "%A %c", iso_time);
    fprintf(log_stream, "[%s] [%s] ", log_level_str, time_buff);

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    vfprintf(log_stream, fmtstring, va_arg_list);
    va_end(va_arg_list);
}
