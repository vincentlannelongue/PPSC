#include "mpi.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>



double term(int i) {
    return 1.0 / (double(i) * double(i));
}

double partial_sum(int i, int j) {
    double sum(0.0);

    // Here we use OpenMP
    #pragma omp parallel for reduction(+:sum)
    for (int k = i; k <= j; k++) {
        sum += term(k);
    }

    return sum;
}

double sum_to_pi(double sum) {
    double pi_approx(std::sqrt(6.0 * sum));
    return pi_approx;
}

bool is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (!is_power_of_two(size)) {
        if (rank == 0) {
            std::cerr << "Error: number of processes must be a power of two" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (argc < 2) {
        if (rank == 0) {
            std::cout << "Needs value n" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int n = std::atoi(argv[1]);

    int chunk_size = n / size;
    int start_index = rank * chunk_size + 1;
    int end_index = (rank == size - 1) ? n : start_index + chunk_size - 1;

    double local_sum = partial_sum(start_index, end_index);
    double global_sum(0.0);

    MPI_Reduce(&local_sum,
               &global_sum,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double computation_time = end_time - start_time;

    if (rank == 0) {
        double pi_approx = sum_to_pi(global_sum);
        std::cout << pi_approx << std::endl;
        double pi(4.0*atan(1.0));
        double error = fabs(pi_approx - pi);
        std::cout << "Error: " << error << std::endl;
        std::cout << "Time: " << computation_time << std::endl;

        std::ofstream outfile;
        outfile.open ("results.txt", std::ios_base::app);
        outfile << std::setprecision(std::numeric_limits<double>::max_digits10);
    
        outfile << size << " " << n << " " << pi_approx << " " << error << " "
        << computation_time << "\n";

        outfile.close();
    }

    MPI_Finalize();
    return 0;
}