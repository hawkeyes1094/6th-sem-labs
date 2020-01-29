// Lab 03, q4

//Read two strings S1 and S2 of same length in root. Using N processes,
// where the string length is evenly divisible by N, produce a resltant
// string in root. Use collective communication functions.

// Written by - Teja Juluru
// Last modified - 29/1/20

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	char str1[100], str2[100],str3[200];
	int str_len;
	char rs1[100], rs2[100], rs[100];
	memset(rs1,'\0',100);
	memset(rs2,'\0',100);
	memset(rs,'\0',100);
	memset(str1,'\0',200);
	memset(str2,'\0',200);
	memset(str3,'\0',200);

	if(rank == 0) {
		printf("Enter string 1 : \n");
		scanf("%s",str1);
		fflush(stdin);

		if(strlen(str1)%size != 0) {
			printf("Enter string with length evenly divisible by no. of processes\n");
			MPI_Abort(MPI_COMM_WORLD,-1);
		}
		printf("Enter string 2 (with length same as str1): \n");
		scanf("%s",str2);
		fflush(stdin);

		if(strlen(str1) != strlen(str2)) {
			printf("Lengths not equal\n");
			MPI_Abort(MPI_COMM_WORLD,-1);
		}
		str_len = strlen(str1);
	}

	MPI_Bcast(&str_len,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(str1,str_len/size,MPI_CHAR,rs1,str_len/size,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(str2,str_len/size,MPI_CHAR,rs2,str_len/size,MPI_CHAR,0,MPI_COMM_WORLD);

	printf("process : %d, rs1 : %s, rs2 : %s\n",rank,rs1,rs2);
	fflush(stdout);

	int i = 0,j = 0;
	while(i < strlen(rs1)+strlen(rs2)) {
		rs[i] = rs1[j];
		i++;
		rs[i] = rs2[j];
		i++;
		j++;
	}

	MPI_Gather(rs,strlen(rs),MPI_CHAR,str3,strlen(rs),MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank == 0) {
		printf("rs : %s\n",str3);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
