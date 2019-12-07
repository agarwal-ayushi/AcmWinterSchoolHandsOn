/*****************************************************************************
About: Serial program to add N elements through function calls to func1 and func2.

Objective: Parallelize the code using single OpenMP region i.e. through use of
           "#pragma omp parallel" construct only once. Other OpenMP constructs may be used.        
*****************************************************************************/
#include<stdio.h>

long int sum1,sum2;

long int func1()
{
   long int j,N=1000000000;
   sum1=0;

#pragma omp for reduction(+:sum1)
   for(j=1;j<N+1;j++)
     sum1=sum1+j;

   return sum1;
};

long int func2()
{
   long int i,N=900000000;
   sum2=0;

#pragma omp for reduction(+:sum2)
   for(i=1;i<N+1;i++)
   sum2=sum2+i;

   return sum2;
};

int main()
{
  long int val1,val2;

#pragma omp parallel 
{
  val1=func1();
  val2=func2();
}

  printf("func1=%ld \nfunc2=%ld \n",val1,val2);

  return 0;
}


