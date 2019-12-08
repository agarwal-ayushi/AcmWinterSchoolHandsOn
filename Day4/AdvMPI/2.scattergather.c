#include <stdio.h>
#include "mpi.h"
#define N 1024
//#define N 64

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW(id+1, p, n) - 1 )
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW(id+1, p, n) - BLOCK_LOW(id, p, n))
#define BLOCK_OWNER(index, p, n) (((p) * ((index)+1)-1)/(n))


int main (int argc, char *argv[])
{

  int rank, size, color, sum=0, localsum=0, i, chunk;
  int arr[N], recv_arr[N], partialsum[N];
  MPI_Status status;
  int newrank, newsize;
  MPI_Comm newcomm;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  //chunk = N/size;
  int pSendInd[size], pSendNum[size];
  pSendInd[0] = 0;
  pSendNum[0] = BLOCK_SIZE(0, size, N);
  for(int i=1; i < size; i++) {
	pSendNum[i] = BLOCK_SIZE(i,size,N);
	pSendInd[i] = pSendInd[i-1] + pSendNum[i-1];
  }

  for (int i=0; i < size; i++) {
//	printf("%d\t%d\n", pSendNum[i], pSendInd[i]);u
  }
  // data initialization
  if (!rank)
  for (i=0; i<N; i++)
     arr[i] = i+1;

  // data distribution
  MPI_Scatterv (&arr, pSendNum, pSendInd, MPI_INT,&recv_arr, pSendNum[rank], MPI_INT,0,MPI_COMM_WORLD);
 
  if (rank == 4) {
	for (int i=0; i < pSendNum[rank]; i++) {
//		printf("%d\n", recv_arr[i]);
	}
  }  
  //perform local sum
  for (int i=0; i < pSendNum[rank]; i++)
    localsum+=recv_arr[i];

  
  // gather local sums
  MPI_Gather (&localsum,1,MPI_INT,&partialsum,1,MPI_INT,0,MPI_COMM_WORLD);

  // rank 0 computes the sums
  if (rank == 0) {
   sum = 0;
   for (i=0; i<size; i++) 
     sum += partialsum[i];
   printf("%d\n", sum);
  }

  MPI_Finalize();
  return 0;

}

