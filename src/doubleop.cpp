#include "doubleop.hpp"

bool eq(const double a, const double b)
{
    return fabs(a - b) <= EPS;
}

bool ne(const double a, const double b)
{
    return !eq(a, b);
}

bool gt(const double a, const double b)
{
    return a - b > EPS;
}

bool lt(const double a, const double b)
{
    return b - a > EPS;
}

bool ge(const double a, const double b)
{
    return gt(a, b) || eq(a, b);
}

bool le(const double a, const double b)
{
    return lt(a, b) || eq(a, b);
}
