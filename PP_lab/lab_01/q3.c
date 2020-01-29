// Lab 01, q3

// MPI program to simulate a simple calculator.

// Written by - Teja Juluru
// last modified - 29/1/20

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int a, b, rank;
	a = 7;
	b = 5;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		printf("%d + %d = %d\n",a,b,a+b);
		fflush(stdout);
	}
	else if(rank == 1) {
		printf("%d - %d  = %d\n",a,b,a-b);
		fflush(stdout);
	}
	else if(rank == 2) {
		printf("%d * %d = %d\n",a,b,a*b);
		fflush(stdout);
	}
	else if(rank == 3) {
		printf("%d / %d = %.3f\n",a,b, (float)a/(float)b);
		fflush(stdout);
	}
	else {

	}

	MPI_Finalize();
	return 0;
}
