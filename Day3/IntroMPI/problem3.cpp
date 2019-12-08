/*****************************************************************************
About: Serial program to multiply two matrices A and B and store into C a
Objective : Use MPI to make the program parallel with correct output.
            Time the serial program, and parallel program with different no. of threads.
*****************************************************************************/

#include<stdio.h>
#include <mpi.h>
#include <iostream> 
using namespace std;
//#define N 3000
#define N 30
int pRank=0;
int pNum=0;

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW(id+1, p, n) - 1 )
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW(id+1, p, n) - BLOCK_LOW(id, p, n))
#define BLOCK_OWNER(index, p, n) (((p) * ((index)+1)-1)/(n))i

void processInit(




int main(int argc, char* argv[])
{
	int x, z, y, pNumRows;
	double *a,*b,*c, *pResult, *pMatrixRows;
 	double start, end;
	double diff_parallel=0.0, diff_serial=0.0, speedup=0.0, average=0.0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &pNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &pRank);
	x = stoi(argv[1]); z = stoi(argv[2]); y = stoi(argv[3]);
	if (pRank == 0) {
		printf("Row-wise matrix matrix multiplication\n");
	}
	processInit(a, b, c, pResult, pMatrixRows, x, z, y, pNumRows);
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i=0; i < 100; i++){
		diff_parallel =0.0;
		start = MPI_Wtime();
		dataDistribution(a, b, pMatrixRows, x, cols, size, pNumRows);
		rowStripeMatrixVectorMul(pMatrixRows, b, pNumRows, cols, pResult);
		resultGather(c, pResult, pNumRows, x);
		end = MPI_Wtime();
		diff_parallel = end - start;
		average += diff_parallel;
	}
	if (pRank == 0) testResult(a, b, c, x, cols, diff_serial);
	average /= 100;
	if (pRank == 0) {
		speedup = diff_serial/average;
		printf("rows = %d\ncols = %d\nSerial Time = %fs\nMPI Time = %fs\nSpeedup = %f\n", x, cols, diff_serial, average, speedup);
	}
	processTerminate(a, b, c, pResult, pMatrixRows);
	MPI_Finalize();
  return 0;
}


