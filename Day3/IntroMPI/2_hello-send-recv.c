/****************************************************************

                  Example 2 (2_hello-send-recv.c)


   Objective           : MPI Program to print "Hello World"
                         This example demonstrates the use of 
                         MPI_Init
                         MPI_Comm_rank
                         MPI_Comm_size
                         MPI_Send
                         MPI_Recv
                         MPI_Finalize

   Input               : Message = "Hello World" 

   Output              : Message and Rank of the process. 

****************************************************************/

#include <stdio.h>
#include "mpi.h"

#define BUFFER_SIZE 20

int main(argc,argv)
int argc;
char *argv[];
{
    int  MyRank,Numprocs, Destination, Source, iproc;
    int  Destination_tag, Source_tag; 
    int  Root = 0;
    char Message[BUFFER_SIZE]; 
/*  ....Status datatype - required in MPI Receive call....*/
    MPI_Status status;

/*....MPI initialization.... */
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 

    if(MyRank != 0)
    {
       sprintf(Message, "Hello World from %d", MyRank);
       Destination = Root;
       Destination_tag = 0;
/*  ....Sending message....*/
       MPI_Send(Message, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, MPI_COMM_WORLD);
    }

    else 
    {
       for(iproc = 1 ; iproc < Numprocs ; iproc++) {
	   Source = iproc;
	   Source_tag = 0;
/*  ....Receiving message....*/
           MPI_Recv(Message, BUFFER_SIZE, MPI_CHAR, Source, Source_tag, MPI_COMM_WORLD, &status);
	   printf("\n %s : Received from Rank %d \n ", Message,iproc);
       }
    }

/*  ....Finalizing the MPI....*/
    MPI_Finalize();
}

