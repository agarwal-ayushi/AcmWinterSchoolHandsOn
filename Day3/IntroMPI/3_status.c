/****************************************************************

                  Example 3 (3_status.c)


   Objective           : MPI Program to know members of MPI_Status datatype (a structure)
                         This example demonstrates the use of wildcards. You can change 
                         tag value and sender rank and see the output
                         MPI_ANY_SOURCE
			 MPI_ANY_TAG

   Input               : Number = 30

   Output              : Rank and Tag value of unknown sender process at receiver side

   Necessary Condition : Minimum number of processes is 4

****************************************************************/

#include<stdio.h>
#include"mpi.h"

int main(int argc, char **argv)
{
 int rank,num;
 MPI_Status status;

 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 if(rank==3)
 { 
   num=30;
   MPI_Send(&num, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);
   printf("Sender side Rank %d: Num=%d \n", rank, num);
 }

 if(rank==1)
 {
/*  ....use of wildcards at receiver side....*/   
   MPI_Recv(&num, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
   printf("Receiver side Rank %d: Num=%d  Source=%d  Tag=%d\n", rank, num, status.MPI_SOURCE, status.MPI_TAG);
 }
 
 MPI_Finalize();

 return 0;
}
