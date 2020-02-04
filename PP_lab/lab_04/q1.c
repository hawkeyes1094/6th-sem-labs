// Lab 04, q1

// find 1! + 2! + .. + N! using MPI_Scan.

// Written by - Teja Juluru
// Created on - 30/1/20
// Last modified - 04/2/20

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int fact = 1, factsum;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for(int i = 1;i <= rank+1;i++)
		fact *= i;

	MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

	if(rank == size-1) {
		printf("Sum of %d factorials = %d\n", size, factsum);
	}

	MPI_Finalize();
	return 0;
}
