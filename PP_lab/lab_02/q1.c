// Lab 02, q1

// MPI program using synchronous send. Sender sends a word to reciever
// reciever toggles each letter of the word and sends it back.

// Written by - Teja Juluru
// Last modified - 16/01/20

#include "mpi.h"
#include <stdio.h>
#include <string.h>
#define MSG_SIZE 100
int main(int argc, char *argv[])
{
	int rank, size;
	char msg[100];
	memset(msg,'\0',100);

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0) {

		printf("Enter a message in master process to send : ");
		fflush(stdout);
		fgets(msg,MSG_SIZE,stdin); //this also inputs a '\n' at the end of the msg
		fflush(stdin);
		MPI_Ssend(msg,MSG_SIZE,MPI_CHAR,1,1,MPI_COMM_WORLD);

		//recieve the message from slave
		MPI_Recv(msg,MSG_SIZE,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		printf("Modified message recieved from slave : %s\n",msg);
		fflush(stdout);

	}
	else {

		MPI_Recv(msg,MSG_SIZE,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		for(int i = 0;i < strlen(msg);i++) {
			if(msg[i] >= 'a' && msg[i] <= 'z') {
				msg[i] -= 32;
			}
			else if(msg[i] >= 'A' && msg[i] <= 'Z') {
				msg[i] += 32;
			}
			else {
				continue;
			}
		}
		MPI_Ssend(msg,MSG_SIZE,MPI_CHAR,0,1,MPI_COMM_WORLD);

	}
	MPI_Finalize();

	return 0;
}
