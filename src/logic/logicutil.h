#include <cstdint>

// Copyright 2022 Nicholas Mazey. All rights reserved
#ifndef GAME_ENGINE_LOGIC_LOGICUTIL_H
#define GAME_ENGINE_LOGIC_LOGICUTIL_H

namespace game_engine
{
namespace logic
{
// converts from degrees into radians
float DegreesToRadians(int degrees);

// converts from radians to degrees
int RadiansToDegrees(float radians);

// simplifies a given angle to between -180 and 180 degrees
int SimplifyAngle(const int degrees);

// simplifies a given angle in radians to between -PI and PI
float SimplifyRadians(const float radians);

// Gives an approximation of sine
float approxsin(const float degrees);

// Gives an approximation of cos
float approxcos(const float degrees);

// Gets epoch time in milliseconds
uint64_t time_ms();
        
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_LOGICUTIL_H