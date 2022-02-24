//Copyright 2022 Nicholas Mazey. All rights reserved
#include "util.h"

#include <math.h>

namespace logic
{
const float PITenDP = 3.1415926535f;

    float degreesToRadians(const int degrees)
    {
        return (degrees * PITenDP) / 180.0f;
    }
    int radiansToDegrees(const float radians)
    {
        return (180.0f * radians) / PITenDP;
    }

    const int simplifyAngle(const int degrees)
    {
        if (-180 <= degrees && degrees <= 180)
        {
            return degrees;
        }
        else
        {
            int newDegrees = degrees % 360;
            if (newDegrees > 180)
            {
                newDegrees = 180 - newDegrees;
            }
            return newDegrees;
        }
    }

    const float simplifyRadians(const float radians)
    {
        if (-1.0f * PITenDP <= radians && radians <= PITenDP)
        {
            return radians;
        }
        else
        {
            float newRad = fmod(radians, (2.0f * PITenDP));
            if (newRad > PITenDP)
            {
                newRad = PITenDP - newRad;
            }
            return newRad;
        }
    }

    const float approxSin(const float radians)
    {
        return sinf(radians);
    }

    const float approxCos(const float radians)
    {
        return cosf(radians);
    }

}