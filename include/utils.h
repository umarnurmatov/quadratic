#pragma once

#define ATTR_UNUSED __attribute__((unused))
#define EXPR_UNUSED(expr) do { (void)expr; } while(0)

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)

static const int BYTE = 8;
