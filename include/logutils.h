#pragma once

// FIXME move headers to cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>

#include "ioutils.h"

/// @brief log level
///        LOG_LEVEL_ERR is the highest priority,
///        LOG_LEVEL_DEBUG is the lowest priority
enum log_level_t
{
    LOG_LEVEL_ERR = 1, // log level 1
    LOG_LEVEL_WARN = 2, // log level 2
    LOG_LEVEL_INFO = 3, // log level 3
    LOG_LEVEL_DEBUG = 4 // log level 4
};

/// @brief initilizes log output file; if file could not be opened
///        stderr is used as output stream
void utils_init_log(void);

/// @brief closes log filestream
void utils_end_log(void);

/// @brief set new global log level
/// @param _log_level_glob new log level, see log_level_t 
void utils_set_global_log_level(enum log_level_t _log_level_glob);

/// @brief converts log_level_t values to string
/// @param log_level log level to convert
/// @return string <LEVEL> 
const char* utils_get_log_level_str(enum log_level_t log_level);

/// @brief logs formatted string to output log stream;
///        use after calling utils_init_log()
/// @param fmtstring 
void utils_log(enum log_level_t log_level, const char* fmtstring, ...)
    __attribute__((format(printf, 2, 3)));
