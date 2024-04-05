#include "../include/trigonometry.h"
#include "../include/const.h"
#include <cmath>

double mth::sin(double arg)
{
    return ::sin(arg * mth::pi / 180);
}
double mth::csc(double arg)
{
    return 1 / mth::sin(arg);
}

double mth::cos(double arg)
{
    return ::cos(arg * mth::pi / 180);
}
double mth::sec(double arg)
{
    return 1 / mth::cos(arg);
}

double mth::tan(double arg)
{
    return ::tan(arg * mth::pi / 180);
}
double mth::cot(double arg)
{
    return 1 / mth::tan(arg);
}

double mth::arcsin(double arg)
{
    return 180 / mth::pi * ::asin(arg);
}
double mth::arccsc(double arg)
{
    return mth::arcsin(1 / arg);
}

double mth::arccos(double arg)
{
    return 180 / mth::pi * ::acos(arg);
}
double mth::arcsec(double arg)
{
    return mth::arccos(1 / arg);
}

double mth::arctan(double arg)
{
    return 180 / mth::pi * ::atan(arg);
}
double mth::arccot(double arg)
{
    return mth::arctan(-arg) + 90;
}