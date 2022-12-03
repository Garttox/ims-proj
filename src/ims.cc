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
    Vec3D rotatedVec = Vec3D(x2, y2, 50);
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

class Projectile : ConditionDown{
    //Integrator vx, vy, vg, yx, yy;
    Integrator y0,y1,y2,y3,zv,zs;
    Parameter drag;
    Vec3D initialVelocity;
    void Action() {
        y1 = 0;
        Out();
        Stop();
    }
public:
    Projectile(Vec3D initialVelocity) :
        ConditionDown(y1),
        /*initialVelocity(initialVelocity),
        drag(0.5 * drag_coefficient * cross_section_area * air_density),
        vy(-((drag * Sqrt(Pow(vy,2) + Pow(vx,2)) * vy)/mass)-gravitational_acceleration, initialVelocity.y),
        vx(-((drag * Sqrt(Pow(vy,2) + Pow(vx,2)) * vx)/mass), initialVelocity.x),
        yx(vx, 0.0),
        yy(vy, 0.0) {};*/
        initialVelocity(initialVelocity),
        drag(0.0046774),
        y0(y2, 0.0),
        y1(y3, 0.0),
        zs(zv, 0.0),
        zv((-drag * Sqrt(y2*y2*zv + y3*y3*zv) * zv )/ mass, initialVelocity.z),
        y2((-drag * Sqrt(y2*y2*zv + y3*y3*zv) * y2 )/ mass, initialVelocity.x),
        y3(((-drag * Sqrt(y2*y2*zv + y3*y3*zv) * y3) / mass) - gravitational_acceleration, initialVelocity.y) {};
    void Out() {
        //Print("%g %g %g\n", yx.Value(), yy.Value(), vx.Value());    
        Print("%g %g %g\n", y0.Value(), zs.Value(), y1.Value());    
    };
};

Projectile projectile(rotate_vector(Vec3D(launch_velocity, 0, 0), angle));

void Sample() { projectile.Out(); }     // output
Sampler S(Sample,0.1);

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
    while ((opt = getopt(argc, argv, ":a:h:")) != -1) {
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

    SetOutput("trajectory.dat");
    Init(0, 1000);    // inicializace experimentu
    SetMethod("rkf5");
    SetAccuracy(1e-7);
    Run();
    Print("Konec simulace");
    return EXIT_SUCCESS;
}