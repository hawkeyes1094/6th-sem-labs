// Lab 04, q4 & q5

// MPI program to read a 4X4 matrix and display the output
// in the given format

// Written by - Teja Juluru
// Created on - 30/1/20
// Last modified - 04/2/20

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void ErrorHandler(int err_code) {
	if(err_code != MPI_SUCCESS) {
		char err_string[100];
		int len_of_err_string;
		int err_class;
		MPI_Error_class(err_code, &err_class);
		MPI_Error_string(err_class, err_string, &len_of_err_string);
		printf("Error class : %s, len = %d\n",err_string, len_of_err_string);
		MPI_Error_string(err_code, err_string, &len_of_err_string);
		printf("Error code : %s, len : %d\n",err_string, len_of_err_string);
	}
}

int main(int argc, char *argv[])
{
	int rank, size, err_code;
	int A[16], B[4], C[4];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size != 4) {
		printf("Use 4 processes only\n");
		MPI_Abort(MPI_COMM_WORLD, -1);
	}

	if(rank == 0) {
		printf("Enter a 4X4 matrix : \n");
		fflush(stdout);
		for(int i = 0;i < 16;i++)
			scanf("%d",&A[i]);
	}

	err_code = MPI_Scatter(A,4,MPI_INT,B,4,MPI_INT,0,MPI_COMM_WORLD);
	ErrorHandler(err_code);
	err_code = MPI_Scan(B,C,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	ErrorHandler(err_code);


	err_code = MPI_Gather(C,4,MPI_INT,A,4,MPI_INT,0,MPI_COMM_WORLD);
	ErrorHandler(err_code);

	if(rank == 0) {
		printf("\n");
		for(int i = 0;i < 16;i++) {
			printf("%d ",A[i]);
			if((i+1)%4 == 0)
				printf("\n");
		}
		printf("\n");
	}
	MPI_Finalize();
	return 0;
}
