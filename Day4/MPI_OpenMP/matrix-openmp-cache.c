/*****************************************************************************
About: OpenMP program to multiply two matrices A and B and store into C matrix
*****************************************************************************/

#include<stdio.h>

#define N 3000
#define BLOCK 40

int main()
{

      int x,y,z,xx,yy,zz;
      double  a[N][N],b[N][N],c[N][N];

      printf("\n    Simple Matrix Multiplication: N=%d\n\n",N);

#pragma omp parallel private(x,y,z,xx,yy,zz) 
{
  #pragma omp for 
     for(x=0;x<N;x=x+1)
       for(y=0;y<N;y=y+1)
        {
          a[x][y]=((y+2)*1.0)/(5.0+x*1.0);
          b[x][y]=((x+y)*1.0)/((y+1)*1.0);
          c[x][y]=0.0;
        }

  #pragma omp for // private(k,j,xx,yy,zz)
  for(x=0;x<N;x=x+BLOCK)
  for(z=0;z<N;z=z+BLOCK)
  for(y=0;y<N;y=y+BLOCK)
        for(xx=x;xx<x+BLOCK && xx<N ;xx=xx+1)
        for(zz=z;zz<z+BLOCK && zz<N ;zz=zz+1)
        for(yy=y;yy<y+BLOCK && yy<N ;yy=yy+1)
              c[xx][yy] = c[xx][yy] + a[xx][zz]*b[zz][yy];
/*
     for(x=0;x<N;x=x+1)
       for(z=0;z<N;z=z+1)
        for(y=0;y<N;y=y+1)
           c[x][y] = c[x][y] + a[x][z]*b[z][y];
*/
}

 printf("%lf\n",c[N-1][N-1]);

 return 0;
}

