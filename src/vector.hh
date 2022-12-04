#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>

struct Vec3D {
    double x;
    double y;
    double z;
    Vec3D(double x, double y, double z) : 
        x(x), y(y), z(z)
        {};
    void printVec() {
        std::cout << "x:" << x << "  y:" << y << std::endl;
    }
};

Vec3D rotateVector(Vec3D vec, double angle);

#endif