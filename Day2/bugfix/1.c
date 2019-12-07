/*****************************************************************************
About: Rectify the compile time error
*****************************************************************************/

#include<stdio.h>

int main()
{

      int x;
      double  a[10];

#pragma omp parallel for 
     for(x=0;x<10;x=x+1)
     {
          a[x]=(5.0+x*1.0);
 	  if(x==0)
             printf("compile time error is rectified now\n");
     }

 return 0;
}

