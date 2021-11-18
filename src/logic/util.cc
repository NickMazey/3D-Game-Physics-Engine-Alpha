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
}