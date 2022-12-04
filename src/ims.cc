/**
 * @file ims.cc
 * @authors Michal trlica - xtrlic02
 *          František Lukeš - xlukes07
 * @brief Program entry point, parsing arguments
 */

#include <iostream>
#include <getopt.h>
#include <math.h>
#include "simlib.h"
#include "util.cc"
#include "vector.hh"
#include "projectile.hh"

struct Parameters {
    double angle;
    double dragCoefficient;
    double relativeHumidity;
    double mass;
    double area;
    double temperature;
    double velocity;
    void printParameters() {
        std::cout << "Angle: " << angle << std::endl;
        std::cout << "Drag coefficient: " << dragCoefficient << std::endl;
        std::cout << "relative humidity: " << relativeHumidity << std::endl;
        std::cout << "Mass: " << mass << std::endl;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Temperature: " << area << std::endl;
        std::cout << "Velocity: " << velocity << std::endl;
    }
};

double celsiusToKelvin(double celsius) {
    double celsiusToKelvinShift = 273.15;
    return celsius + celsiusToKelvinShift;
}

//calculations taken from https://www.calctool.org/atmospheric-thermodynamics/air-density
double calculateWaterVaperPressure(double tempK, double relativeHumidity) {
    double tempC = tempK - 273.15;
    double c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, p_t, E_st;
    c0 = 0.99999683;
    c1 = -0.90826951e-2;
    c2 = 0.78736169e-4;
    c3 = -0.61117958e-6;
    c4 = 0.43884187e-8;
    c5 = -0.29883885e-10;
    c6 = 0.21874425e-12;
    c7 = -0.17892321e-14;
    c8 = 0.11112018e-16;
    c9 = -0.30994571e-19;
    p_t = c0 + tempC*(c1 + tempC*(c2 + tempC*(c3 + tempC*(c4 + tempC*(c5 + tempC*(c6 + tempC*(c7+ tempC*(c8 + tempC*c9))))))));
    E_st = 6.1078/pow(p_t, 8);
    return relativeHumidity * E_st;
}

double handleArgument(char *optarg, char *p, int opt) {
    double val;
    val = strtod(optarg, &p);
    if (*p != '\0' || (opt != 't' && val < 0)) { // Only temperature can be a negative number
		std::cerr << "Bad argument value for argument " << (char)opt << std::endl;
        errorUsage();
	}
    return val;
}

//default parameters
double _angle = 45;
double _launch_velocity = 827; // [m/s]
Vec3D _initialVelocity = rotateVector(Vec3D(_launch_velocity, 0, 0), _angle); //
double _dragCoef = 0.3;
double _mass = 43.2;
double _crossSection = 0.0765;
double _temperatureK = celsiusToKelvin(0);
double _waterVaporPressure = calculateWaterVaperPressure(_temperatureK, 0);
Projectile projectile(_initialVelocity, _mass, _dragCoef, _crossSection, _temperatureK, _waterVaporPressure);

void Sample() {
    projectile.Out(); 
};
Sampler S(Sample,0.1);

int main(int argc, char *argv[]) {
    
    if (argc < 13) {
        std::cerr << "Too few arguments" << std::endl;
        errorUsage();
    }

    int opt;
    bool errFlag = false;
    char *p = NULL;
    /**
     * opts
     * a - howitzer firing angle
     * c - drag coefficient
     * h - relative huminity
     * m - projectile mass
     * o - output file name
     * s - projectile cross-section area
     * t - temperature
     * v - initial projectile velocity
     */
    Parameters parameters;
    std::string outputFile = "trajectory.dat"; // default output file
    int mandatoryArgsEncountered = 0;
    while ((opt = getopt(argc, argv, ":a:c:h:m:o:s:t:v:")) != -1) {
        switch(opt) {
            case 'a':
                parameters.angle = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'c':
                parameters.dragCoefficient = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'h':
                parameters.relativeHumidity = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'm':
                parameters.mass = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 's':
                parameters.area = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 't':
                parameters.temperature = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'v':
                parameters.velocity = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case ':':
                std::cerr << "Missing argument for option: " << (char)optopt << std::endl;
                return 1;
            case '?':
                std::cerr << "Unknown option: " << (char)optopt << std::endl;
                return 1;
            default:
                errorUsage();
        }
    }

    if (mandatoryArgsEncountered != 7) {
        std::cerr << "Missing some of the required parameters" << std::endl;
        errorUsage();
    }

    for(; optind < argc; optind++) {
        std::cerr << "Unrecognized argument: " << argv[optind] << std::endl;
        errFlag = true;
    }

    if (errFlag) {
        errorUsage();
    }

    Vec3D initialVelocity(parameters.velocity, 0.0, 0.0);
    double tempK = celsiusToKelvin(parameters.temperature);
    double waterVaporPressure = calculateWaterVaperPressure(tempK, parameters.relativeHumidity);
    initialVelocity = rotateVector(initialVelocity, parameters.angle);
    projectile.SetDragCoef(parameters.dragCoefficient);
    projectile.SetInitialVelocity(initialVelocity);
    projectile.SetMass(parameters.mass);
    projectile.SetCrossSection(parameters.area);
    projectile.SetTemperatureK(tempK);
    projectile.SetWaterVaporPressure(waterVaporPressure);
    SetOutput(outputFile.data());
    Init(0, 1000);    // init simulation
    SetMethod("rkf5");
    SetAccuracy(1e-7);
    Run();
    Print("Konec simulace");
    return EXIT_SUCCESS;
}