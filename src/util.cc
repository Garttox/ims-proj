/**
 * @file util.cc
 * @authors Michal trlica - xtrlic02
 *          František Lukeš - xlukes07
 * @brief Utility print and exit functions
 */

#include <iostream>

/**
 * Print usage
 */
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

/**
 * Print usage and exit with error code 1
 */
void errorUsage() {
    usage();
    exit(EXIT_FAILURE);
}