/*****************************************************************************
About: Serial program to multiply two matrices A and B and store into C matrix
Objective : Use OpenMP to make the program parallel with correct output.
            Time the serial program, and parallel program with different no. of threads.
*****************************************************************************/

#include<stdio.h>

#define N 3000

int main()
{

      int x,y,z;
      double  a[N][N],b[N][N],c[N][N];

      printf("\n    Simple Matrix Multiplication: N=%d\n\n",N);

     for(x=0;x<N;x=x+1)
       for(y=0;y<N;y=y+1)
        {
          a[x][y]=((y+2)*1.0)/(5.0+x*1.0);
          b[x][y]=((x+y)*1.0)/((y+1)*1.0);
          c[x][y]=0.0;
        }

     for(x=0;x<N;x=x+1)
       for(z=0;z<N;z=z+1)
        for(y=0;y<N;y=y+1)
           c[x][y] = c[x][y] + a[x][z]*b[z][y];

       printf("%lf\n",c[N-1][N-1]);

 return 0;
}

