#include "util.h"
#include <math.h>
namespace logic{
    #define PI 3.1415926535f
    float degreesToRadians(const int degrees){
    return (degrees * PI) / 180.0f;
}
    int radiansToDegrees(const float radians){
        return (180.0f * radians) / PI;
    }

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

    const float simplifyRadians(const float radians){
        if(-1.0f * PI <= radians && radians <= PI){
            return radians;
        } else{
            float newRad = fmod(radians,(2.0f * PI));
            if(newRad > PI){
                newRad = PI - newRad;
            }
            return newRad;
        }
    }

    const float approxSin(const float radians){
        //Based off of Bhaskara I's sine approximation formula, with the ability to do negative angles as well
        /*
        float x = simplifyRadians(radians);
        bool isNegative = false;
        if(x < 0){
            isNegative = true;
        }
        float sine = (16.0f * fabs(x) * (PI - fabs(x))) / (5.0f * pow(PI,2.0f) - 4.0f * fabs(x) * (PI - fabs(x)));
        if(isNegative){
            sine = 0.0f - sine;
        }
        return sine;
        */
       return sinf(radians);
    }

    const float approxCos(const float radians){
        /*
        return approxSin(radians + PI/2.0f);
        */
       return cosf(radians);
    }
    #undef PI

}