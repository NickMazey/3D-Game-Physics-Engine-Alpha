#ifndef GAME_ENGINE_LOGIC_UTIL_H
#define GAME_ENGINE_LOGIC_UTIL_H
namespace logic{
    double degreesToRadians(double degrees);
    int radiansToDegrees(double radians);
    
    //simplifies a given angle to between -180 and 180 degrees
    const int simplifyAngle(const int degrees);
}
#endif //GAME_ENGINE_LOGIC_UTIL_H