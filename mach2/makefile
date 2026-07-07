comp:
	mpic++ -fopenmp -O2 main.cpp -o main

run:
	OMP_NUM_THREADS=2 mpirun -n 4 ./main 10

clear:
	rm -rf out.log main