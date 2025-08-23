#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "assertutils.h"

static const char* ANSI_COLOR_RED    = "\x1b[1;31m";
static const char* ANSI_COLOR_GREEN  = "\x1b[1;32m";
static const char* ANSI_COLOR_YELLOW = "\x1b[1;33m";
static const char* ANSI_COLOR_BLUE   = "\x1b[1;34m";

static const char* ANSI_COLOR_BOLD_WHITE  = "\x1b[1;38;5;15m";
static const char* ANSI_COLOR_BOLD_RED    = "\x1b[1;38;5;160m";
static const char* ANSI_COLOR_BOLD_GREEN  = "\x1b[1;38;5;82m";
static const char* ANSI_COLOR_BOLD_YELLOW = "\x1b[1;38;5;226m";
static const char* ANSI_COLOR_BOLD_BLUE   = "\x1b[1;38;5;20m";

static const char* ANSI_COLOR_RESET       = "\x1b[0m";

void utils_colored_fprintf(FILE* stream, const char* mode, const char* fmtstring, ...);
