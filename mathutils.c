#include "mathutils.h"

int equal_with_precision(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

int equal_zero(double a)
{
    return equal_with_precision(a, ZERO);
}

int gt_zero(double a)
{
    return (!equal_zero(a)) && (a > ZERO);
}

int lt_zero(double a)
{
    return (!equal_zero(a)) && (a < ZERO);
}