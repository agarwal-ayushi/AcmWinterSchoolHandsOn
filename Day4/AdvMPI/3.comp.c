#include <stdio.h>
#include "mpi.h"
#define N 1024*1024

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

  chunk = N/size;

  // data initialization
  if (!rank)
  for (i=0; i<N; i++)
     arr[i] = i+1;

  // data distribution
  double  start=MPI_Wtime();
  MPI_Scatter (&arr,chunk,MPI_INT,&recv_arr,chunk,MPI_INT,0,MPI_COMM_WORLD);
  double scatter_time = MPI_Wtime() - start;
  if (rank == 0)  printf("Scatter time is =%f\n", scatter_time);

  start = MPI_Wtime();
  if (rank == 0) {
	for (int i=1; i < size; i++)
	  	MPI_Send(&arr, chunk, MPI_INT, i, i, MPI_COMM_WORLD);
  }
  if(rank) {
 	MPI_Recv(&recv_arr, chunk, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
  }

  double send_recv_time = MPI_Wtime() - start;

  if (rank == 0) {
	printf("Send/Recv Time is = %f\n", send_recv_time);
	printf("%f\n", send_recv_time-scatter_time);
  }
  MPI_Finalize();
  return 0;

}

