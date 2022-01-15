#include "util.h"
namespace logic{
    #define PI 3.1415926535
    double degreesToRadians(double degrees){
    return (degrees * PI) / 180.0;
}
    int radiansToDegrees(double radians){
        return (180.0 * radians) / PI;
    }
    #undef PI

    const int simplifyAngle(const int degrees){
        if(-180 <= degrees && degrees <= 180){
            return degrees;
        } else if(degrees < -180){
            int newDegrees = degrees % -360;
            if(-180 <= newDegrees && newDegrees <= 180){
                return newDegrees;
            } else{
                return newDegrees + 360;
            }
        }else {
            int newDegrees = degrees % 360;
            if(-180 <= newDegrees && newDegrees <= 180){
                return newDegrees;
            } else{
                return newDegrees - 360;
            }
        }
    }
}