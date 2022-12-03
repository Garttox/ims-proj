#include <iostream>
#include <getopt.h>
#include <errno.h>
#include <limits.h> // for INT_MIN and INT_MAX
#include <math.h>
#include "simlib.h"

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

//TODO: print usage
void usage() {
    std::cerr << "usage" << std::endl;
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

int main(int argc, char *argv[]) {
    
    if (argc < 5) {
        std::cerr << "Too few arguments" << std::endl;
        error_usage();
    }

    int opt;
    bool err_flag = false;
    char *p;
    /**
     * opts
     * a - howitzer firing angle
     * h - howitzer altitude
     */
    double angle;
    long conv;
    int altitude;
    std::string output_file = "trajectory.dat"; // default output file
    while ((opt = getopt(argc, argv, ":a:h:o:")) != -1) {
        switch(opt) {
            case 'a':
                angle = strtod(optarg, &p);
                if (*p != '\0' || angle < 0) {
					std::cerr << "Bad \"-a\" argument value" << std::endl;
                    error_usage();
				}
                break;
            case 'h':
                conv = strtol(optarg, &p, 10);
                if (*p != '\0' || errno != 0) {
                    std::cerr << "Bad \"-h\" argument value" << std::endl;
                    error_usage();
                }
                if (conv < INT_MIN || conv > INT_MAX) {
                    std::cerr << "\"-h\" argument value out of integer bounds" << std::endl;
                    error_usage();
                }
                altitude = conv;
                break;
            case 'o':
                output_file = optarg;
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

    SetOutput(output_file.data());
    Init(0, 1000);    // inicializace experimentu
    SetMethod("rkf5");
    SetAccuracy(1e-7);
    Run();
    Print("Konec simulace");
    return EXIT_SUCCESS;
}