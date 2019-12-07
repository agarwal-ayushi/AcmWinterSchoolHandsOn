/*****************************************************************************
About: The code should print ranks of all four threads.
Bug:   Thread rank variable named tid is shared by default in parallel region. 
       Try with both Intel (icc -qopenmp) and GNU (gcc -fopenmp) compilers before and after making changes.
 * *****************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include "omp.h" 

int main()
{
 int tid;

omp_set_num_threads(4);

#pragma omp parallel private(tid)
{
   tid = omp_get_thread_num();

   if(tid % 2 == 0)
     sleep(1);

   printf("My thread rank is %d\n", tid);
}

 return 0;
}


