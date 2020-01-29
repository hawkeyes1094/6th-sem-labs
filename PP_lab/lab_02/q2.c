// Lab 02, q2

// MPI program where the master process sends a number to each of the slave processes.
// Slaves print the numbers. Standard send is used.

// Written by - Teja Juluru
// Last modified - 16/01/20

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0) {

		for(int i = 1;i < size;i++) {
			x = i;
			MPI_Send(&x,1,MPI_INT,i,1,MPI_COMM_WORLD);
		}

	}
	else {

		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("recieved %d in process %d\n",x,rank);
		fflush(stdout);
	}
	MPI_Finalize();

	return 0;
}
