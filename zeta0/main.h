#include <cmath>
#include <cstdlib>


double term(int i) {
    return 1.0 / (i * i);
}


double partial_sum(int i, int j) {
        double sum(0.0);
        for (int k = i; k <= j; k++) {
            sum += term(k);
        }
        return sum;   
    }

double sum_to_pi(double sum) {
    double pi_approx(std::sqrt(6.0 * sum));
    return pi_approx;
}