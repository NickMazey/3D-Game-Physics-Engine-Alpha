// Copyright 2022 Nicholas Mazey. All rights reserved
#include "logicutil.h"

#include <math.h>
namespace game_engine
{
    namespace logic
    {
        const float kPITenDP = 3.1415926535f;

        float DegreesToRadians(const int degrees)
        {
            return (degrees * kPITenDP) / 180.0f;
        }
        int RadiansToDegrees(const float radians)
        {
            return (180.0f * radians) / kPITenDP;
        }

        const int SimplifyAngle(const int degrees)
        {
            if (-180 <= degrees && degrees <= 180)
            {
                return degrees;
            }
            else
            {
                int new_degrees = degrees % 360;
                if (new_degrees > 180)
                {
                    new_degrees = 180 - new_degrees;
                }
                return new_degrees;
            }
        }

        const float SimplifyRadians(const float radians)
        {
            if (-1.0f * kPITenDP <= radians && radians <= kPITenDP)
            {
                return radians;
            }
            else
            {
                float new_rad = fmod(radians, (2.0f * kPITenDP));
                if (new_rad > kPITenDP)
                {
                    new_rad = kPITenDP - new_rad;
                }
                return new_rad;
            }
        }

        const float approxsin(const float radians)
        {
            return sinf(radians);
        }

        const float approxcos(const float radians)
        {
            return cosf(radians);
        }

    } // namespace logic
} // namespace game_engine