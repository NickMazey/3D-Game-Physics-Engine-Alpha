//Copyright 2022 Nicholas Mazey. All rights reserved
#ifndef GAME_ENGINE_LOGIC_UTIL_H
#define GAME_ENGINE_LOGIC_UTIL_H
namespace logic
{
    //converts from degrees into radians
    float DegreesToRadians(int degrees);

    //converts from radians to degrees
    int RadiansToDegrees(float radians);

    //simplifies a given angle to between -180 and 180 degrees
    const int SimplifyAngle(const int degrees);

    //simplifies a given angle in radians to between -PI and PI
    const float SimplifyRadians(const float radians);

    //Gives an approximation of sine
    const float approxsin(const float degrees);

    //Gives an approximation of cos
    const float approxcos(const float degrees);
}
#endif //GAME_ENGINE_LOGIC_UTIL_H