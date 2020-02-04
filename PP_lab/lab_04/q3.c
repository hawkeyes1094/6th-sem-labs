// Lab 04, q3

// read a 3*3 matrix. Enter element to be searchedi n root.
// Find number of occurences of this element in the matrix
// using three porcesses.

// Written by - Teja Juluru
// Created on - 30/1/20
// Last modified - 04/2/20

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int A[9], B[9], search, s_count, sum;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size != 3) {
		printf("Use only 3 processes\n");
		MPI_Abort(MPI_COMM_WORLD, -1);
	}
	if(rank == 0) {

		printf("Enter a 3 X 3 matrix : \n");
		fflush(stdout);
		for(int i = 0;i < 9;i++)
			scanf("%d",&A[i]);
		printf("Enter element to be searched : ");
		fflush(stdout);
		scanf("%d",&search);
	}
	MPI_Bcast(&search,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(A,3,MPI_INT,B,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i = 0;i < 3;i++) {
		if(B[i] == search)
			s_count++;
	}

	MPI_Reduce(&s_count,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank == 0) {
		printf("no. of %d's in the matrix is : %d\n",search,sum);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
