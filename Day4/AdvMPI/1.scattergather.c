#include <stdio.h>
#include "mpi.h"
#define N 1024*1024

int main (int argc, char *argv[])
{

  int rank, size, color, i;
  double sum=0, localsum=0, chunk;
  double arr[N], recv_arr[N], partialsum[N];
  MPI_Status status;
  int newrank, newsize;
  MPI_Comm newcomm;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  chunk = N/size;

  // data initialization
  if (!rank)
  for (i=0; i<N; i++)
     arr[i] = i+1;

  // data distribution
  MPI_Scatter (&arr,chunk,MPI_DOUBLE,&recv_arr,chunk,MPI_DOUBLE,0,MPI_COMM_WORLD);
  
  //perform local sum
  for (int i=0; i < chunk; i++)
    localsum+=recv_arr[i];

  
  // gather local sums
  MPI_Gather (&localsum,1,MPI_DOUBLE,&partialsum,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

  // rank 0 computes the sums
  if (rank == 0) {
   sum = 0;
   for (i=0; i<size; i++) 
     sum += partialsum[i];
   printf("%f\n", sum);
  }

  MPI_Finalize();
  return 0;

}

