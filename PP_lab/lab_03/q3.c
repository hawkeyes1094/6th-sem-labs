// Lab 03, q3

// Read a string. Using N processes, where the string length is evenly
// divisible by N, find the number of non-vowels in the string. In root,
// print the number of non-vowels found by each process and print the
// total number of non-vowels.

// Written by - Teja Juluru
// Last modified - 29/1/20

#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank,size;
	char vowels[] = "aeiouAEIOU";
	char str[100];
	memset(str,'\0',100);
	long str_len;
	char rs[100];
	memset(rs,'\0',100);

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0) {
		printf("Enter the string (without spaces) : \n");
		fflush(stdout);
		scanf("%s",str);

		str_len = strlen(str);
		if(str_len % size != 0) {
			printf("Enter a string with length evenly divisible by no. of processes %d\n",size);
			MPI_Abort(MPI_COMM_WORLD,-1);
		}
	}

	MPI_Bcast(&str_len,1,MPI_LONG,0,MPI_COMM_WORLD);

	MPI_Scatter(str,str_len/size,MPI_CHAR,rs,str_len/size,MPI_CHAR,0,MPI_COMM_WORLD);

	int non_vowels = 0;
	int nv_count[size];

	int flag;
	for(int i = 0;i < strlen(rs);i++) {
		flag = 0;
		for(int j = 0;j < strlen(vowels);j++) {
			if(rs[i] == vowels[j])
				flag = 1;
		}
		if(flag == 0)
			non_vowels++;
	}

	MPI_Gather(&non_vowels,1,MPI_INT,nv_count,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0) {
		non_vowels = 0;
		for(int i = 0;i < size;i++) {
			printf("In process %d, no. of non-vowels found : %d\n",i+1,nv_count[i]);
			non_vowels += nv_count[i];
		}
		printf("Total non-vowel count is %d\n",non_vowels);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
