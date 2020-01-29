// Lab 02, q1

// MPI program where the root process reads N values. Root process sends
// one value to each process. each process finds the factorial and returns
// it to the root process. Root process gathers the factorial and sums it.

// Written by - Teja Juluru
// Last modified - 22/01/20

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int arr[size];
	int num;
	long factorial = 1;
	long gather_factorials[size];
	if(rank == 0) {
		printf("Enter %d values : ",size);
		fflush(stdout);
		for(int i = 0;i < size;i++)
			scanf("%d",&arr[i]);
	}

	MPI_Scatter(arr,1,MPI_INT,&num,1,MPI_INT,0,MPI_COMM_WORLD);

	for(int i = 1;i <= num;i++)
		factorial *= i;

	MPI_Gather(&factorial,1,MPI_LONG,gather_factorials,1,MPI_LONG,0,MPI_COMM_WORLD);

	if(rank == 0) {
		factorial = 0;
		for(int i = 0;i < size;i++)
			factorial += gather_factorials[i];

		printf("Sum of factorials is : %ld\n",factorial);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
