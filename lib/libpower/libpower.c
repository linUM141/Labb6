// Daniel Hammarberg
// 2017-02-16

#include "libpower.h"

float calc_power_r(float volt, float resistance)
{
    if (volt < epsilon || resistance < epsilon)
    {
        return -1;
    }
    return volt * volt / resistance;
}

float calc_power_i(float volt, float current)
{
    if (volt < epsilon || current < epsilon)
    {
        return -1;
    }
    return volt * current;
}

