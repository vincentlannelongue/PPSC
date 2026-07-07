#include <cmath>
#include <cstdlib>


double term(int i, double x) {
    return pow(-1.0, i-1)*(pow(x, 2*i-1)/(2*i-1));
}


// double term_zeta(int i) {
//     return 1.0 / (double(i) * double(i));
// }

double partial_sum(int i, int j, double x) {
        double sum(0.0);
        for (int k = i; k <= j; k++) {
            sum += term(k, x);
            // sum += term_zeta(k);

        }
        return sum;   
    }

double partial_pi(int i, int j) {
    return 16*partial_sum(i, j, (1.0/5.0)) - 4*partial_sum(i, j, (1.0/239.0));
}

double compute_pi(int n) {
    return 16*partial_sum(1, n, (1.0/5.0)) - 4*partial_sum(1, n, (1.0/239.0));
}