// lab 04, example 1

// Using N processes, find the sum of N factorials. Use MPI_Reduce

// Written by - Teja Juluru
// Created on - 30/1/20
// Last modified - 04/2/20

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int fact = 1, factsum, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	for(int i = 1;i <= rank+1;i++)
		fact = fact*i;

	MPI_Reduce(&fact,&factsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
		printf("Sum of all factorials = %d\n",factsum);

	MPI_Finalize();
	return 0;
}
