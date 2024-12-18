/**
 * @file projectile.hh
 * @authors Michal trlica - xtrlic02
 *          František Lukeš - xlukes07
 * @brief Projectile simulation object
 */

#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include "simlib.h"
#include "vector.hh"

// constants
const double gravitationalAcceleration = 9.80665;// gravitational acceleration [m/s]
const double molarMassOfAir = 0.0289644; // molar mass of dry air [kg/mol]
const double universalGasConstant = 8.31423; // universal / ideal gas constant [m^3 * Pa * K^-1 * mol^-1]
const double gasConstantDryAir = 287.05; // gas constant of dry air [J/(kg*K)]
const double gasConstantWaterVapor = 461.495; // gas constant of water vapor [J/(kg*K)]
const double seaLevelPressure = 101325; // air pressure at sea level [Pa]

class Projectile : ConditionDown{
private:
    Integrator vx, vy, vz; // projectile speed
    Integrator yx, yy, yz; // projectile position
    Parameter mass, dragCoef, crossSection, temperatureK, waterVaporPressure; //constant simulation parameters
    Expression airPressure, airDensity, drag;
    void Action();
public:
    Projectile(Vec3D _initialVelocity, double _mass, double _dragCoef, double _crossSection, double _temperatureK, double _waterVaporPressure);
    void Out();
    void SetInitialVelocity(Vec3D _initialVelocity);
    void SetDragCoef(double _dragCoef);
    void SetMass(double _mass);
    void SetCrossSection(double _crossSection);
    void SetTemperatureK(double _temperatureK);
    void SetWaterVaporPressure(double _relativeHumidity);
};

#endif