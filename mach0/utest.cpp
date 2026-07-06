#include <iostream>
#include <cmath>
#include <cstdlib>
#include "main.h"

int main(int argc, char* argv[]) {

    double pi_approx = compute_pi(3);

    double expected(0.0);
    double x1 = 1.0/5.0;
    double x2 = 1.0/239.0;

    double sum1(0.0);
    sum1 += x1 - pow(x1,3)/3.0 + pow(x1,5)/5.0;

    double sum2(0.0);
    sum2 += x2 - pow(x2,3)/3.0 + pow(x2,5)/5.0;

    expected = 16.0*sum1 - 4.0*sum2;

    if (std::abs(pi_approx - expected) < 1e-6) { std::cout << "Test passed\n"; }
    else { std::cout << "Test failed\n"; }

    return 0;
}
