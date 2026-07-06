#include "mpi.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include "main.h"


bool is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << "Rank = " << rank << ", Size = " << size << std::endl;
    if (!is_power_of_two(size)) {
        if (rank == 0) {
            std::cerr << "Error: number of processes must be a power of two" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (argc < 2) {
        if (rank == 0) {
            std::cout << "Needs n" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int n = std::atoi(argv[1]);

    int chunk_size = n / size;
    int start_index = rank * chunk_size + 1;
    int end_index = (rank == size - 1) ? n : start_index + chunk_size - 1;

    double local_sum = partial_sum(start_index, end_index);
    double global_sum = 0.0;

    MPI_Reduce(&local_sum,
               &global_sum,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);


    if (rank == 0) {
        double pi = sum_to_pi(global_sum);
        std::cout << pi << std::endl;
        std::cout << "Hello from rank " << rank << std::endl;
    }

    MPI_Finalize();
    return 0;
}