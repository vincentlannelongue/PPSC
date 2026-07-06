#include <iostream>
#include <cmath>
#include <cstdlib>
#include "main.h"

int main(int argc, char* argv[]) {
    if (argc < 2)
        {
            std::cout << "Needs n" << std::endl;
            return 1;
        }
    int n = std::atoi(argv[1]);

    double sum = partial_sum(1, n);
    double pi_approx = sum_to_pi(sum);

    std::cout << pi_approx << std::endl;

    return 0;
} 
