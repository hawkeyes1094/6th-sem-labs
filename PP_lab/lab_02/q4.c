// Lab 02, q4

// MPI program reads an int in root process. Root sends to process1,
// process1 sends this value to process2 and so on. Last process
// sends the value back to root. Before sending, each process will
// increment the recieved value by one.

// Written by - Teja Juluru
// Last modified - 16/01/20

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int x;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(size < 2){
		printf("use more than 1 process\n");
		exit(-1);
	}

	if(rank == 0) {

		printf("Enter a value : ");
		fflush(stdout);
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Recv(&x,1,MPI_INT,size-1,1,MPI_COMM_WORLD,&status);
		printf("root process recieved %d from process %d\n",x,size-1);

	}
	else {

		MPI_Recv(&x,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
		printf("In process %d, recieved %d from process %d\n",rank,x,rank-1);
		x += 1;
		MPI_Send(&x,1,MPI_INT,(rank+1)%size,1,MPI_COMM_WORLD);

	}
	MPI_Finalize();

	return 0;
}
