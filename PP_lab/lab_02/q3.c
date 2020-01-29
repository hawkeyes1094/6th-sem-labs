// Lab 02, q3

// MPI program to read N elements of the array in the root process.
// N is equal to the number of process.
// Root process sends one value to each slave.
// Buffered send is used.

// Written by - Teja Juluru
// Last modified - 16/01/20

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	int arr[size-1];
	int x;

	int buf_size = 100;
	int buf[buf_size];
	MPI_Buffer_attach(buf,buf_size);

	if(rank == 0) {
		printf("Enter %d numbers : ",size-1);
		fflush(stdout);
		for(int i = 0;i < size-1;i++)
			scanf("%d",&arr[i]);

		for(int i = 1;i < size;i++) {
			MPI_Bsend(&arr[i-1],1,MPI_INT,i,1,MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		if(rank % 2 == 0) { //even ranked processes
			printf("Process %d recieved : %d, squared : %d\n",rank,x,x*x);
		}
		else { //odd ranked processes
			printf("Process %d recieved : %d, cubed : %d\n",rank,x,x*x*x);
		}
	}

	MPI_Buffer_detach(buf,&buf_size);
	MPI_Finalize();

	return 0;
}
