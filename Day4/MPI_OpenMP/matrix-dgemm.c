/*****************************************************************************
About: Serial program to multiply two matrices A and B and store into C matrix
*****************************************************************************/

#include<stdio.h>
#include<omp.h>
#include<mkl.h>

#define N 10000

int main()
{

      int x,y,z;
      double  a[N][N],b[N][N],c[N][N];

      printf("\n    BLAS Matrix Multiplication: N=%d\n",N);

#pragma omp parallel for private(y)
     for(x=0;x<N;x=x+1)
       for(y=0;y<N;y=y+1)
        {
          a[x][y]=((y+2)*1.0)/(5.0+x*1.0);
          b[x][y]=((x+y)*1.0)/((y+1)*1.0);
          c[x][y]=0.0;
        }
 
 cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,N,N,N,1.0,a[0],N,b[0],N,0.0,c[0],N);

      printf("%lf\n",c[N-1][N-1]);

 return 0;
}

