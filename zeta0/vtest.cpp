#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>
#include "main.h"


int main(int argc, char* argv[]) {
    double pi(4.0*atan(1.0));
    std::ofstream outfile;
    outfile.open ("vtest_results.txt");
    outfile << std::setprecision(std::numeric_limits<double>::max_digits10);

    for (int exp = 1; exp <= 24; exp++) {
        double sum = partial_sum(1, pow(2, exp));
        double pi_approx = sum_to_pi(sum);
        double error = fabs(pi_approx - pi);

        outfile << exp << " " << pi_approx << " " << error << "\n";
    }

    outfile.close();

    return 0;
} 
