#include <iostream>
#include <getopt.h>
#include <math.h>
#include "simlib.h"

struct Parameters {
    double angle;
    double dragCoefficient;
    double mass;
    double area;
    double temperature;
    double velocity;
    void printParameters() {
        std::cout << "Angle: " << angle << std::endl;
        std::cout << "Drag coefficient: " << dragCoefficient << std::endl;
        std::cout << "Mass: " << mass << std::endl;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Temperature: " << area << std::endl;
        std::cout << "Velocity: " << velocity << std::endl;
    }
};

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

Vec3D rotateVector(Vec3D vec, double angle) {
    double radians = (M_PI / 180) * angle;
    double x2 = cos(radians) * vec.x - sin(radians) * vec.y;
    double y2 = sin(radians) * vec.x + cos(radians) * vec.y;
    Vec3D rotatedVec = Vec3D(x2, y2, 0);
    vec.printVec();
    return rotatedVec;
}

/*
const double mass = 43.2; // projectile mass [kg]
const double launch_velocity = 100; // projectile launch velocity [m/s]
const double cross_section_area = 0.0765; // cross-section area of projectile [m^2]

const double drag_coefficient = 0.3;
const double air_density = 0.037325;

const double angle = 45;
const double crossSectionArea = 0.0765; // cross-section area of m107 projectile [m^2]*/
const double gravitationalAcceleration = 9.80665;// gravitational acceleration
const double molarMassOfAir = 0.0289644; // molar mass of dry air [kg/mol]
const double universalGasConstant = 8.31423; // universal / ideal gas constant
const double gasConstantDryAir = 287.05; // gas constant of dry air
const double seaLevelPressure = 101325; // air pressure at sea level
/*
y'' = -drag * |y'| * y' / mass -g
drag = 0.5 * drag_coef * cross_section * air_density
*/
class Projectile : ConditionDown{
    Integrator vx, vy, vz, yx, yy, yz;
    //Integrator y0,y1,y2,y3,zv,zs;
    Parameter mass, dragCoef, crossSection, temperatureK;
    Expression airPressure, airDensity, drag;
    Parameter p0x, p0y, p0z;
    Vec3D initialVelocity;
    void Action() { // projectile touched "ground"
        yy = 0; // correction
        Out();
        Stop();
    }
public:
    Projectile(Vec3D _initialVelocity, double _mass, double _dragCoef, double _crossSection, double _temperatureK) :
        ConditionDown(yy),
        mass(_mass), dragCoef(_dragCoef), crossSection(_crossSection), temperatureK(_temperatureK), // init const Parameters
        p0x(_initialVelocity.x),
        p0y(_initialVelocity.y),
        p0z(_initialVelocity.z),
        airPressure(seaLevelPressure * Exp((-gravitationalAcceleration * molarMassOfAir * yy)/(universalGasConstant * temperatureK))),
        airDensity(airPressure/(gasConstantDryAir * temperatureK)),
        //drag(0.5 * drag_coefficient * cross_section_area * air_density),
        drag(0.5 * dragCoef * crossSection * airDensity),
        //drag(_drag),
        initialVelocity(_initialVelocity),
        yx(vx, 0.0),
        yy(vy, 0.0),
        yz(vz, 0.0),
        vx((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vx) / mass, p0x.Value()),
        vy(((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vy) / mass) - gravitationalAcceleration, p0y.Value()),
        vz((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * vz) / mass, p0z.Value()) {};
    void Out() {
        //Print("%g %g %g\n", yx.Value(), yy.Value(), vx.Value());    
        Print("%g %g %g\n", yx.Value(), yz.Value(), yy.Value()); //print current position at sample time
    };
    void SetInitialVelocity(Vec3D _initialVelocity) {
        vx.Init(_initialVelocity.x);
        vy.Init(_initialVelocity.y);
        vz.Init(_initialVelocity.z);
    };
    void SetDragCoef(double _dragCoef) {
        dragCoef = _dragCoef;
    };
    void SetMass(double _mass) {
        mass = _mass;
    };
    void SetCrossSection(double _crossSection) {
        crossSection = _crossSection;
    };
    void SetTemperatureK(double _temperatureK) {
        temperatureK = _temperatureK;
    };
};

double celsiusToKelvin(double celsius) {
    double celsiusToKelvinShift = 273.15;
    return celsius + celsiusToKelvinShift;
}

void usage() {
    std::cout << "Usage: ./ims -a # -c # -m # [-o filename] -s # -t # -v #" << std::endl;
    std::cout << "-a: howitzer firing angle [°]" << std::endl;
    std::cout << "-c: drag coefficient" << std::endl;
    std::cout << "-m: projectile mass [kg]" << std::endl;
    std::cout << "-o: output file name" << std::endl;
    std::cout << "-s: projectile cross-section area [m^2]" << std::endl;
    std::cout << "-t: temperature [°C]" << std::endl;
    std::cout << "-v: initial projectile velocity [m/s]" << std::endl;
}

void errorUsage() {
    usage();
    exit(1);
}

double handleArgument(char *optarg, char *p, int opt) {
    double val;
    val = strtod(optarg, &p);
    if (*p != '\0' || val < 0) {
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
//Projectile(Vec3D _initialVelocity, double _mass, double _dragCoef, double _crossSection, double _temperatureK) :
Projectile projectile(_initialVelocity, _mass, _dragCoef, _crossSection, _temperatureK);

void Sample() { projectile.Out(); };
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
     * m - projectile mass
     * o - output file name
     * s - projectile cross-section area
     * t - temperature
     * v - initial projectile velocity
     */
    Parameters parameters;
    std::string outputFile = "trajectory.dat"; // default output file
    int mandatoryArgsEncountered = 0;
    while ((opt = getopt(argc, argv, ":a:c:m:o:s:t:v:")) != -1) {
        switch(opt) {
            case 'a':
                parameters.angle = handleArgument(optarg, p, opt);
                mandatoryArgsEncountered++;
                break;
            case 'c':
                parameters.dragCoefficient = handleArgument(optarg, p, opt);
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

    if (mandatoryArgsEncountered != 6) {
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
    initialVelocity = rotateVector(initialVelocity, parameters.angle);
    projectile.SetDragCoef(parameters.dragCoefficient);
    projectile.SetInitialVelocity(initialVelocity);
    projectile.SetMass(parameters.mass);
    projectile.SetCrossSection(parameters.area);
    projectile.SetTemperatureK(tempK);
    SetOutput(outputFile.data());
    Init(0, 1000);    // inicializace experimentu
    SetMethod("rkf5");
    SetAccuracy(1e-7);
    Run();
    Print("Konec simulace");
    return EXIT_SUCCESS;
}