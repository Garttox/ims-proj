#include <iostream>
#include <getopt.h>
#include <errno.h>
#include <limits.h> // for INT_MIN and INT_MAX
#include "simlib.h"
#include "simlib3D.h"

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

    return EXIT_SUCCESS;
}