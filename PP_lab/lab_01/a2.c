// lab 01, a2

// MPI program to find primes between 1 and 100 using two processes.

// Written by - Teja Juluru
// Last modified - 29/1/20

#include <stdio.h>
#include <mpi.h>

int CheckPrime(int n) {
	if(n < 2)
		return 0;
	for(int i = 2;i <= n/2;i++) {
		if(n % i == 0)
			return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		printf("Process 0 will check between 1 and 50\n");
		fflush(stdout);
		for(int i = 2;i <= 50;i++) {
			if(CheckPrime(i)) {
				printf("Process 0, %d\n",i);
				fflush(stdout);
			}
		}
	}
	else if(rank == 1) {
		printf("Process 1 will check between 51 and 100\n");
		fflush(stdout);
		for(int i = 51;i <= 100;i++) {
			if(CheckPrime(i)) {
				printf("Process 1, %d\n",i);
				fflush(stdout);
			}
		}
	}

	MPI_Finalize();
	return 0;
}
