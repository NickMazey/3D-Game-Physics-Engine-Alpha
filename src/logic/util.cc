#include "util.h"
#include <math.h>
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
        } else {
            int newDegrees = degrees % 360;
            if(newDegrees > 180){
                newDegrees = 180 - newDegrees;
            } 
            return newDegrees;
        }
    }

    //Based off of Bhaskara I's sine approximation formula, with the ability to do negative angles as well
    const float approxSin(const int degrees){
        int x = simplifyAngle(degrees);
        float sine = (4.0f * abs(x) * (180.0f - abs(x))) / (40500.0f - abs(x) * (180.0f - abs(x)));
        if(x <= 0){
            sine *= -1.0f;
        }
        return sine;
    }

    const float approxCos(const int degrees){
        return approxSin(degrees + 90);
    }
}