// Lab 03, q6

// Perform the given operation using N processes. The output
// elements are displayed in the root.

// Written by - Teja Juluru
// Last modified - 29/1/20
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int arr1[100];
	int arr2[100];
	int n1,n2;
	if(rank == 0) {
		printf("Enter number of elements (should be divisible by %d) : ",size);
		fflush(stdout);
		scanf("%d",&n1);
		if(n1 % size != 0) {
			printf("Invalid number\n");
			MPI_Abort(MPI_COMM_WORLD,-1);
		}
		printf("Enter the elements : \n");
		fflush(stdout);
		for(int i = 0;i < n1;i++)
			scanf("%d",&arr1[i]);
		n2 = n1/size;
	}

	MPI_Bcast(&n2,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(arr1,n2,MPI_INT,arr2,n2,MPI_INT,0,MPI_COMM_WORLD);

	for(int i = 1;i < n2;i++) {
		arr2[i] += arr2[i-1];
	}

	MPI_Gather(arr2,n2,MPI_INT,arr1,n2,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0) {
		printf("Resultant array : \n");
		for(int i = 0;i < n1;i++) {
			printf("%d ",arr1[i]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
