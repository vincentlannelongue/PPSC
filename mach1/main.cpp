#include "mpi.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>
#include "main.h"


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

    double local_sum_1 = partial_sum(start_index, end_index, (1.0/5.0));
    double local_sum_2 = partial_sum(start_index, end_index, (1.0/239.0));

    double global_sum_1(0.0);
    double global_sum_2(0.0);

    MPI_Reduce(&local_sum_1,
               &global_sum_1,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    MPI_Reduce(&local_sum_2,
               &global_sum_2,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double computation_time = end_time - start_time;

    if (rank == 0) {
        double pi_approx = 16*global_sum_1 - 4*global_sum_2;

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