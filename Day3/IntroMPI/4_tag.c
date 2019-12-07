/****************************************************************

                  Example 4 (4_tag.c)


   Objective           : MPI Program to know significance of MPI TAG values
                         Unintentional This example demonstrates the use of wildcards
                         MPI_ANY_SOURCE
                         MPI_ANY_TAG

   Input               : Two messages - age and weight 

   Output              : Wrong messages received at receiver side

   Necessary Condition : Minimum number of processes is 2

****************************************************************/

#include<stdio.h>
#include"mpi.h"

int main(int argc, char **argv)
{
 int rank,age,weight;
 MPI_Status status;

 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);

 if(rank==0)
 { 
   age=30;
   weight=70;
   MPI_Send(&age,    1, MPI_INT, 1, 101, MPI_COMM_WORLD);
   MPI_Send(&weight, 1, MPI_INT, 1, 201, MPI_COMM_WORLD);
   printf("Sent Message: Age=%d  Weight=%d\n",age,weight);
 }

 if(rank==1)
 {
   MPI_Recv(&age,    1, MPI_INT, 0, 201, MPI_COMM_WORLD, &status);
   MPI_Recv(&weight, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
   printf("Received Message: Age=%d  Weight=%d\n",age,weight);
 }
 
 MPI_Finalize();

 return 0;
}
