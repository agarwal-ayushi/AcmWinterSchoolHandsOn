/********************************************************************

                      Example 6  (6_buffered.c)

  Objective            : To understand that for large messages MPI Buffered send may
  			 have better performance than regular send call 
                         This example demonstrates the use of
                         MPI_Bsend
                         MPI_Buffer_attach

  Input               : Small and Large messages 

  Output              : Less wait at sender side due to MPI Buffered send call

********************************************************************/

#include<stdio.h>
#include"mpi.h"

#define N 100 

int main(int argc, char **argv)
{
 int rank,i,a[N],buf[N+10];
 MPI_Status status;

 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);

/*....Create extra MPI buffer....*/
// MPI_Buffer_attach(buf,4*(N+10));
 if(rank==0)
 { 
   for(i=0;i<N;i++)
     a[i]=i;
   system("echo -n Time before send call : ; date");

/*....MPI Buffered Send....*/
   MPI_Send(a,N,MPI_INT,1,101,MPI_COMM_WORLD);

   system("echo -n Time after send call : ; date");
 }

 if(rank==1)
 {
/*....Delay introduced at receiver side....*/
   sleep(5);
   MPI_Recv(a,N,MPI_INT,0,101,MPI_COMM_WORLD,&status);
 }
 
 MPI_Finalize();

 return 0;
}
