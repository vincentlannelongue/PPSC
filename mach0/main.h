#include <cmath>
#include <cstdlib>


double term(int i, double x) {
    return pow(-1.0, i-1)*(pow(x, 2*i-1)/(2*i-1));
}


double partial_sum(int i, int j, double x) {
        double sum(0.0);
        for (int k = i; k <= j; k++) {
            sum += term(k, x);
        }
        return sum;   
    }

double compute_pi(int n) {
    return 16*partial_sum(1, n, (1.0/5.0)) - 4*partial_sum(1, n, (1.0/239.0));
}