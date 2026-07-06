#include <iostream>
#include <cmath>
#include <cstdlib>
#include "main.h"

int main(int argc, char* argv[]) {

    double sum = partial_sum(1, 3);
    double pi_approx = sum_to_pi(sum);
    double expected(0.0);
    expected += 1.0 + 1.0/4.0 + 1.0/9.0;
    expected = std::sqrt(6.0 * expected);

    if (std::abs(pi_approx - expected) < 1e-6) { std::cout << "Test passed\n"; }
    else { std::cout << "Test failed\n"; }

    return 0;
} 
