#ifndef GAME_ENGINE_LOGIC_UTIL_H
#define GAME_ENGINE_LOGIC_UTIL_H
namespace logic{
    float degreesToRadians(int degrees);
    int radiansToDegrees(float radians);
    
    //simplifies a given angle to between -180 and 180 degrees
    const int simplifyAngle(const int degrees);

    //simplifies a given angle in radians to between -PI and PI
    const float simplifyRadians(const float radians);

    //Gives an approximation of sine
    const float approxSin(const float degrees);

    //Gives an approximation of cos
    const float approxCos(const float degrees);
}
#endif //GAME_ENGINE_LOGIC_UTIL_H