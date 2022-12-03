#include <iostream>
#include <getopt.h>
#include <math.h>
#include "simlib.h"

struct Parameters {
    double angle;
    double dragCoefficient;
    double density;
    double mass;
    double area;
    double velocity;
    void printParameters() {
        std::cout << "Angle: " << angle << std::endl;
        std::cout << "Drag coefficient: " << dragCoefficient << std::endl;
        std::cout << "Density: " << density << std::endl;
        std::cout << "Mass: " << mass << std::endl;
        std::cout << "Area: " << area << std::endl;
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

Vec3D rotate_vector(Vec3D vec, double angle) {
    double radians = (M_PI / 180) * angle;
    double x2 = cos(radians) * vec.x - sin(radians) * vec.y;
    double y2 = sin(radians) * vec.x + cos(radians) * vec.y;
    Vec3D rotatedVec = Vec3D(x2, y2, 70);
    vec.printVec();
    return rotatedVec;
}

const double mass = 43.2; // projectile mass [kg]
const double launch_velocity = 100; // projectile launch velocity [m/s]
const double cross_section_area = 0.0765; // cross-section area of projectile [m^2]
const double gravitational_acceleration = 9.80665;// gravitational acceleration

const double drag_coefficient = 0.3;
const double air_density = 0.037325;

const double angle = 45;
const Vec3D wind_speed(1,1,1);
/*
y'' = -drag * |y'| * y' / mass -g
drag = 0.5 * drag_coef * cross_section * air_density
*/
class Projectile : ConditionDown{
    Integrator vx, vy, vz, yx, yy, yz;
    //Integrator y0,y1,y2,y3,zv,zs;
    Parameter drag;
    void Action() { // projectile touched "ground"
        yy = 0; // correction
        Out();
        Stop();
    }
public:
    Projectile(Vec3D initialVelocity) :
        ConditionDown(yy),
        drag(0.5 * drag_coefficient * cross_section_area * air_density),
        yx(vx, 0.0),
        yy(vy, 0.0),
        yz(vz, 0.0),
        vx((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * wind_speed.x * vx) / mass, initialVelocity.x),
        vy(((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * wind_speed.y * vy) / mass) - gravitational_acceleration, initialVelocity.y),
        vz((-drag * Sqrt(vx*vx + vy*vy + vz*vz) * wind_speed.z * vz) / mass, initialVelocity.z) {};
    void Out() {
        //Print("%g %g %g\n", yx.Value(), yy.Value(), vx.Value());    
        Print("%g %g %g\n", yx.Value(), yz.Value(), yy.Value()); //print current position
    };
};

void usage() {
    std::cout << "Usage: ./ims -a # -c # -d # -m # [-o filename] -s # -v #" << std::endl;
    std::cout << "-a: howitzer firing angle" << std::endl;
    std::cout << "-c: drag coefficient" << std::endl;
    std::cout << "-d: air density" << std::endl;
    std::cout << "-m: projectile mass" << std::endl;
    std::cout << "-o: output file name" << std::endl;
    std::cout << "-s: projectile cross-section area" << std::endl;
    std::cout << "-v: initial projectile velocity" << std::endl;
}

void error_usage() {
    usage();
    exit(1);
}

void error_exit(std::string message, int exit_code) {
    std::cerr << message << std::endl;
    exit(exit_code);
}

Projectile projectile(rotate_vector(Vec3D(launch_velocity, 0, 0), angle));

void Sample() { projectile.Out(); };
Sampler S(Sample,0.1);

double handleArgument(char *optarg, char *p, int opt) {
    double val;
    val = strtod(optarg, &p);
    if (*p != '\0' || angle < 0) {
		std::cerr << "Bad argument value for argument " << (char)opt << std::endl;
        error_usage();
	}
    return val;
}

int main(int argc, char *argv[]) {
    
    if (argc < 5) {
        std::cerr << "Too few arguments" << std::endl;
        error_usage();
    }

    int opt;
    bool err_flag = false;
    char *p = NULL;
    /**
     * opts
     * a - howitzer firing angle
     * c - drag coefficient
     * d - air density
     * m - projectile mass
     * o - output file name
     * s - projectile cross-section area
     * v - initial projectile velocity
     */
    Parameters parameters;
    std::string output_file = "trajectory.dat"; // default output file
    while ((opt = getopt(argc, argv, ":a:c:d:m:o:s:v:")) != -1) {
        switch(opt) {
            case 'a':
                parameters.angle = handleArgument(optarg, p, opt);
                break;
            case 'c':
                parameters.dragCoefficient = handleArgument(optarg, p, opt);
                break;
            case 'd':
                parameters.density = handleArgument(optarg, p, opt);
                break;
            case 'm':
                parameters.mass = handleArgument(optarg, p, opt);
                break;
            case 'o':
                output_file = optarg;
                break;
            case 's':
                parameters.area = handleArgument(optarg, p, opt);
                break;
            case 'v':
                parameters.velocity = handleArgument(optarg, p, opt);
                break;
            case '?':
                std::cerr << "Unknown option: " << optarg << std::endl;
                return 1;
            default:
                error_usage();
        }
    }

    for(; optind < argc; optind++) {
        std::cerr << "Unrecognized argument: " << argv[optind] << std::endl;
        err_flag = true;
    }

    if (err_flag) {
        error_usage();
    }
    parameters.printParameters();
    SetOutput(output_file.data());
    Init(0, 1000);    // inicializace experimentu
    SetMethod("rkf5");
    SetAccuracy(1e-7);
    Run();
    Print("Konec simulace");
    return EXIT_SUCCESS;
}