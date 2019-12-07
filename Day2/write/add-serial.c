/*****************************************************************************
About     : Serial program to add N elements
Objective : Use OpenMP to make the program parallel with correct output. 
	    Time the serial program, and parallel program with different no. of threads.
********************************************************************************/


#include<stdio.h>

#define N 1000000000

int main()
{
 long int i,a[N],sum=0;

 for(i=0;i<N;i++)
 {
  a[i]=i+1;
 }

 for(i=0;i<N;i++)
 {
  sum=sum+a[i];
 }
  printf("Sum=%ld  \n",sum);

 return 0;
}


