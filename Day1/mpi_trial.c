#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]) {
	MPI_Init(NULL,NULL);
	printf("Hello HPC World\n");
	return 0;
}
