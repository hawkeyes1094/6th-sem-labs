// Lab 02, a3

// MPI program reads a value 'n' in the root process. Using N processes,
// including root, find out 1!+(1+2)+3!+(1+2+3+4)+5!+....+n! or
// (1+2+3+...n) depending on wether 'n' is odd or even and print the
// result in the root process.

// Written by - Teja Juluru
// Last modified - 29/01/20

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int rank, size, x;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Status status;

  if(rank == 0) {
    int n;
    printf("Enter a value less than or equal to %d : ",size);
    fflush(stdout);
    scanf("%d",&n);

	if(n > size) {
		printf("Fatal Error\n");
		fflush(stdout);
		MPI_Abort(MPI_COMM_WORLD,-1);
	}
	// Send the value to all processes. The processes with rank greater
	// than 'n' do not do any computations.
    for(int i = 1;i < size;i++)
    	MPI_Send(&n,1,MPI_INT,i,0,MPI_COMM_WORLD);

	long ans = 1;
	if(n % 2 == 0) {
		for(int i = 1;i < n;i++) {
			MPI_Recv(&x,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
			ans += x;
		}
		printf("%d is even. Result = %ld\n",n,ans);
		fflush(stdout);
	}
	else {
		for(int i = 1;i < n;i++) {
			MPI_Recv(&x,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
			ans += x;
		}
		printf("%d is odd. Result = %ld\n",n,ans);
		fflush(stdout);
	}
  }
  else {
	MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);

	if(rank < x) { // the processes which help in computing the answer.
		if(x % 2 == 0) {
			x = rank + 1;
			MPI_Send(&x,1,MPI_INT,0,0,MPI_COMM_WORLD);
		}
		else {
			if(rank % 2 == 1) {
				x = (rank + 1) * (rank + 2) / 2;
				MPI_Send(&x,1,MPI_INT,0,0,MPI_COMM_WORLD);
			}
			else {
				x = 1;
				for(int i = 1;i <= rank+1;i++)
					x *= i;
				MPI_Send(&x,1,MPI_INT,0,0,MPI_COMM_WORLD);
			}
		}
	}
	else {
		// for processes with rank >= x which do not do any computations.
		// This is done to end all the processes safely.
	}
  }

  MPI_Finalize();
  return 0;
}
