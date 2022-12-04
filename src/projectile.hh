#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include "simlib.h"
#include "vector.hh"

// constants
const double gravitationalAcceleration = 9.80665;// gravitational acceleration
const double molarMassOfAir = 0.0289644; // molar mass of dry air [kg/mol]
const double universalGasConstant = 8.31423; // universal / ideal gas constant
const double gasConstantDryAir = 287.05; // gas constant of dry air
const double seaLevelPressure = 101325; // air pressure at sea level

class Projectile : ConditionDown{
private:
    Integrator vx, vy, vz; // projectile speed
    Integrator yx, yy, yz; // projectile position
    Parameter mass, dragCoef, crossSection, temperatureK; //constant simulation parameters
    Expression airPressure, airDensity, drag;
    void Action();
public:
    Projectile(Vec3D _initialVelocity, double _mass, double _dragCoef, double _crossSection, double _temperatureK);
    void Out();
    void SetInitialVelocity(Vec3D _initialVelocity);
    void SetDragCoef(double _dragCoef);
    void SetMass(double _mass);
    void SetCrossSection(double _crossSection);
    void SetTemperatureK(double _temperatureK);
};

#endif