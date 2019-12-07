/*****************************************************************************
About: Change the data scope to print the final value of "num" as it would be printed in serial code 
*****************************************************************************/

#include<stdio.h>
#include "omp.h"

int main()
{

 int x,num=0;

omp_set_num_threads(6);

#pragma omp parallel for lastprivate(num)
  for(x=0;x<10;x=x+1)
      num=x;

if(num == 9)
  printf("Final value of num = 9 in parallel code is correct\n");
else
  printf("Final value of num in serial code = 9. In parallel code it is = %d. Hence, not correct\n",num);

 return 0;
}

