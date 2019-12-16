//Module(s) to be loaded
//module load cuda/10.1
//Compilation:
//nvcc mm-blas.cu -lcublas
//Execution: ./a.out

#include<stdio.h>
#include<cuda.h>
#include<cublas.h>

#define N 15000

int main()
{
  double a[N][N] __attribute__((aligned(64)));
  double b[N][N] __attribute__((aligned(64)));
  double c[N][N] __attribute__((aligned(64)));
  double *da,*db,*dc;
  int i,j;
  printf("MM: N=%d  \n",N);

  for(i=0;i<N;i++)
   for(j=0;j<N;j++)
   {
     a[i][j]=(i%4 - j%6)*2.0;
     b[i][j]=(j%3 + i%7)*3.0;
     c[i][j]=0.0;
   }

   cublasAlloc(N*N,8,(void **) &da);
   cublasAlloc(N*N,8,(void **) &db);
   cublasAlloc(N*N,8,(void **) &dc);

   cublasSetMatrix(N,N,8,a,N,da,N);
   cublasSetMatrix(N,N,8,b,N,db,N);
   cublasSetMatrix(N,N,8,c,N,dc,N);

   cublasDgemm('n','n',N,N,N,1.0,db,N,da,N,0.0,dc,N);

   cublasGetMatrix(N,N,8,dc,N,c,N);

  printf("%lf  %lf  %lf  %lf\n",c[100][200],c[500][400],c[1000][1000],c[N-1][N-1]);
/*
  for(i=0;i<N;i++) {
   for(j=0;j<N;j++)
     printf("%lf ",a[i][j]);
     printf("\n"); }

 printf("\n");

  for(i=0;i<N;i++) {
   for(j=0;j<N;j++)
     printf("%lf ",b[i][j]);
     printf("\n"); }

 printf("\n");

  for(i=0;i<N;i++) {
   for(j=0;j<N;j++)
     printf("%lf ",c[i][j]);
     printf("\n"); }

 printf("\n");
*/
 return 0;
}

//module unload gcc/7.1.0 module load cuda/9.0  nvcc mm-blas.cu -lcublas  watch -n .1 nvidia-smi 
