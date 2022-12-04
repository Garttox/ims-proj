/**
 * @file vector.cc
 * @authors Michal trlica - xtrlic02
 *          František Lukeš - xlukes07
 */

#include <math.h>
#include "vector.hh"

Vec3D rotateVector(Vec3D vec, double angle) {
    double radians = (M_PI / 180) * angle;
    double x2 = cos(radians) * vec.x - sin(radians) * vec.y;
    double y2 = sin(radians) * vec.x + cos(radians) * vec.y;
    Vec3D rotatedVec = Vec3D(x2, y2, 0);
    vec.printVec();
    return rotatedVec;
}