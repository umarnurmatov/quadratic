#pragma once

#define ATTR_UNUSED __attribute__((unused))
#define EXPR_UNUSED(expr) do { (void)expr; } while(0)
