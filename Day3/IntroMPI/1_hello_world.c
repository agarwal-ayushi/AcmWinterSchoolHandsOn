/****************************************************************

                  Example 1 (1_hello_world.c)	


   Objective           : MPI Program to print "Hello World"
                         This example demonstrates the use of 
                         MPI_Init
                         MPI_Comm_rank
                         MPI_Comm_size
                         MPI_Finalize

****************************************************************/

/* ....Standard Includes.... */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(argc,argv)
int argc;
char *argv[];
{
    int  MyRank,Numprocs, Destination, Source, iproc;
    MPI_Status status;

    /*....MPI initialization.... */    
    MPI_Init(&argc,&argv);

    /*....Finding MPI Rank of every process.... */    
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    /*....Finding total number of MPI processes.... */    
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 

    printf("\n Rank=%d Total=%d\n",MyRank,Numprocs);

    /*  ....Finalizing the MPI....*/
    MPI_Finalize();
}


