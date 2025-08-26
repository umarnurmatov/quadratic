#pragma once

#include <stdio.h>

#include "assertutils.h"

#define UNUSED __attribute__((unused))

UNUSED static const char* ANSI_COLOR_RED    = "\x1b[1;31m";
UNUSED static const char* ANSI_COLOR_GREEN  = "\x1b[1;32m";
UNUSED static const char* ANSI_COLOR_YELLOW = "\x1b[1;33m";
UNUSED static const char* ANSI_COLOR_BLUE   = "\x1b[1;34m";

UNUSED static const char* ANSI_COLOR_BOLD_WHITE  = "\x1b[1;38;5;15m";
UNUSED static const char* ANSI_COLOR_BOLD_RED    = "\x1b[1;38;5;160m";
UNUSED static const char* ANSI_COLOR_BOLD_GREEN  = "\x1b[1;38;5;82m";
UNUSED static const char* ANSI_COLOR_BOLD_YELLOW = "\x1b[1;38;5;226m";
UNUSED static const char* ANSI_COLOR_BOLD_BLUE   = "\x1b[1;38;5;20m";

UNUSED static const char* ANSI_COLOR_RESET       = "\x1b[0m";

/// @brief function to print text with ANSI mode; checks if stream is console
/// @param stream output stream
/// @param mode ANSI color mode 
/// @param fmtstring formatted string 
void utils_colored_fprintf(FILE* stream, const char* mode, const char* fmtstring, ...)
    __attribute__ ((format (printf, 3, 4)));
