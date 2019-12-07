/********************************************************************

                      Example 7  (7_non-blocking.c)

  Objective            : To understand that for non-uniform computations across 
			 sender and receiver processes, non-blocking send and receive
                         generally has better performance than blocking calls
                         This example demonstrates the use of
                         MPI_Isend
                         MPI_Wait

  Input               : Array of data. Delay is introduced at receiver side

  Output              : Computation and Communication overlap

********************************************************************/

#include<stdio.h>
#include"mpi.h"

#define N 100000

int main(int argc, char **argv)
{
 int rank,i,a[N];
 MPI_Status status;
 MPI_Request request;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 if(rank==0)
 { 
   for(i=0;i<N;i++)
     a[i]=i;

   system("echo -n Time before non-blocking send call : ;date");

/*....MPI non-blocking send....*/
   MPI_Isend(a,N,MPI_INT,1,101,MPI_COMM_WORLD,&request);
   system("echo -n Time after non-blocking send call : ;date");

// Other computations can be done here. Send data buffer must not be modified here

/*....MPI wait till receiver has received the data....*/
   MPI_Wait(&request,&status);
   system("echo -n Time after wait call : ;date");

// Send data buffer can be safely modified now
   a[N-1]=100;
 }

 if(rank==1)
 {
/*....Delay introduced at receiver side....*/
  //sleep(5);

  MPI_Recv(a,N,MPI_INT,0,101,MPI_COMM_WORLD,&status);
  printf("\nLast element received by Rank=%d = %d\n\n",rank,a[N-1]);
 }
 
 MPI_Finalize();

 return 0;
}
