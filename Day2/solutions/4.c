/*****************************************************************************
About: Rectify the compile time error and subsequently run the code for few times
*****************************************************************************/

#include<stdio.h>
#include "omp.h"

int main()
{

      int rank;

#pragma omp parallel private(rank) num_threads(3)
{
  rank=omp_get_thread_num();

  #pragma omp sections 
  { 
    #pragma omp section 
    {
      printf("Thread %d inside section\n",rank);  
    }

    #pragma omp section 
    {
      printf("Thread %d inside section\n",rank);  
    }
  }
}

 return 0;
}

