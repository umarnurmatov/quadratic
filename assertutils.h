#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "colorutils.h"

#define utils_assert(expression) !!(expression) \
                                    ? (void)(0) \
                                    : utils_assert_fail(#expression, __FILE__, __LINE__)

/// @brief processes assertion failure case; see utils_assert macro
/// @param expression string containing asserted expression; passed by macro
void utils_assert_fail(const char* expression, const char* filename, int linenumber);