/**
 * @file projectile.cc
 * @authors Michal trlica - xtrlic02
 *          František Lukeš - xlukes07
 */

#include "projectile.hh"

// private
void Projectile::Action() { // projectile touched "ground"
    yy = 0; // correction - if current iteration is <0, then correct height to 0
    Out();
    Stop();
}
// public
/**
 * Projectile simulation equations
 * 
 * y'' = -drag * |y'| * y' / mass -g
 * drag = 0.5 * drag_coef * cross_section * air_density
 * air_density = airPressure/(gasConstantDryAir * temperatureK)
 * airPressure = seaLevelPressure * exp((-gravitationalAcceleration * molarMassOfAir * y'')/(universalGasConstant * temperatureK))
 */
Projectile::Projectile(Vec3D _initialVelocity, double _mass, double _dragCoef, double _crossSection, double _temperatureK, double _waterVaporPressure) :
    ConditionDown(yy),
    mass(_mass), dragCoef(_dragCoef), crossSection(_crossSection), temperatureK(_temperatureK), // init const Parameters
    waterVaporPressure(_waterVaporPressure),
    airPressure(seaLevelPressure * Exp((-gravitationalAcceleration * molarMassOfAir * yy)/(universalGasConstant * temperatureK))),
    //airDensity(airPressure/(gasConstantDryAir * temperatureK)),
    airDensity((airPressure - waterVaporPressure)/(gasConstantDryAir*temperatureK) + waterVaporPressure/(gasConstantWaterVapor*temperatureK)),
    drag(0.5 * dragCoef * crossSection * airDensity),
    yx(vx, 0.0),
    yy(vy, 0.0),
    yz(vz, 0.0),
    vx((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vx) / mass, _initialVelocity.x),
    vy(((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vy) / mass) - gravitationalAcceleration, _initialVelocity.y),
    vz((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vz) / mass, _initialVelocity.z) {};
void Projectile::Out() {
    Print("%g %g %g\n", yx.Value(), yz.Value(), yy.Value()); //print current position at sample time
};
void Projectile::SetInitialVelocity(Vec3D _initialVelocity) {
    vx.Init(_initialVelocity.x);
    vy.Init(_initialVelocity.y);
    vz.Init(_initialVelocity.z);
};
void Projectile::SetDragCoef(double _dragCoef) {
    dragCoef = _dragCoef;
};
void Projectile::SetMass(double _mass) {
    mass = _mass;
};
void Projectile::SetCrossSection(double _crossSection) {
    crossSection = _crossSection;
};
void Projectile::SetTemperatureK(double _temperatureK) {
    temperatureK = _temperatureK;
};
void Projectile::SetWaterVaporPressure(double _waterVaporPressure) {
    waterVaporPressure = _waterVaporPressure;
}