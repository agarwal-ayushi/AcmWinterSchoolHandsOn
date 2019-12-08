#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  char hostname[64], cnode[20];
  int rank, size, len, color1, color2, newrank1, newrank2;
  int value, minval, min, i, j=-1;
  MPI_Comm newcomm1, newcomm2;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  srand(time(NULL));
  value = abs((size-rank)*(82019-rand()))%1000;

  // get processor name
  MPI_Get_processor_name(hostname, &len);

  // get node number
  for (i=0; i<len; i++)
    if (isdigit(hostname[i]))
      cnode[++j]=hostname[i];
  cnode[++j]='\0';
  sscanf(cnode, "%d", &color1);

//MPI_Comm_split
//MPI_Comm_rank //use newrank1  

//  MPI_Reduce (destination = minval) 

  color2 = newrank1;
  MPI_Comm_split (MPI_COMM_WORLD, color2, rank, &newcomm2);
  MPI_Comm_rank (newcomm2, &newrank2);
  if (!newrank1)
  MPI_Reduce (&minval, &min, 1, MPI_INT, MPI_MIN, 0, newcomm2);

  if (!rank) printf ("%d %d\n", rank, min);

  MPI_Finalize();
  return 0;
}

