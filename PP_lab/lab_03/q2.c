// Lab 03, q2

// MPI program to read a value M and N*M values in the root process.
// Root process sends M elements to each process. Each process finds
// the average and sends these values to root. Root collects all
// values and finds the total average.

// Written by - Teja Juluru
// Last modified - 22/1/20

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int* elements;
	int m;
	if(rank == 0) {
		printf("Enter value of m : ");
		fflush(stdout);
		scanf("%d",&m);

		elements = (int*)malloc(sizeof(int) * size*m);

		printf("Enter elements : \n");
		fflush(stdout);
		for(int i = 0;i < size*m;i++) {
			scanf("%d",&elements[i]);
		}
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

	int arr[m]; //array in which processes recieve
	double avg = 0;
	double averages[size];

	MPI_Scatter(elements,m,MPI_INT,arr,m,MPI_INT,0,MPI_COMM_WORLD);

	for(int i = 0;i < m;i++)
		avg += arr[i];
	avg = avg/(double)m;

	MPI_Gather(&avg,1,MPI_DOUBLE,averages,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

	if(rank == 0) {
		double res = 0;
		for(int i = 0;i < size;i++)
			res += averages[i];

		res = res/(double)size;
		printf("Resultant average is : %lf\n",res);
		fflush(stdout);
	}

	MPI_Finalize();

	return 0;
}
