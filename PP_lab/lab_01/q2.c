// Lab 01, q2

// MPI program where even ranked processes print "Hello" and
// odd ranked processes print "world".

// Written by - Teja Juluru
// Last modified - 29/1/20

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank % 2 == 0) {
		printf("process %d, Hello\n", rank);
		fflush(stdout);
	}
	else {
		printf("process %d, world\n", rank);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
