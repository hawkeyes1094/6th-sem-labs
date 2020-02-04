// Lab 04, q2

// MPI program to calculate the value of Pi by integrating
// 4/(1+x^2) over the limits 0 to 1. Area under the curve
// is divided into rectangles and the rectangles are
// distributed to the processes.

// Written by - Teja Juluru
// Created on - 04/2/20
// Last modified - 04/2/20

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double lower_limit, upper_limit, mid_point;
	lower_limit = (1/(double)size)*(rank);
	upper_limit = (1/(double)size)*(rank+1);
	mid_point = (lower_limit + upper_limit) / 2;

	double area, integral;
	area = (upper_limit - lower_limit) * (4/(1 + mid_point*mid_point));

	MPI_Reduce(&area, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank == 0) {
		printf("Integral = %lf\n",integral);
	}

	MPI_Finalize();
	return 0;
}
