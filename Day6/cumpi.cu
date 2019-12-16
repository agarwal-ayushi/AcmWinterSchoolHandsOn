//Module(s) to be loaded
//module load cuda/10.1
//module load pgi/openmpi/3.1.3/2019
//Compilation:
//nvcc cumpi.cu -I/opt/pgi/linux86-64-llvm/19.4/mpi/openmpi-3.1.3/include -L/opt/pgi/linux86-64-llvm/19.4/mpi/openmpi-3.1.3/lib -lmpi
//Execution : mpirun -n 2 ./a.out



#include<stdio.h>
#include"mpi.h"
#include"cuda.h"
#define N  1000

__global__ void ckrnl(int *add)
{
  int j;
  for(j=0;j<N;j++)
    add[j]=add[j]+6;
  return;
}

int main(int argc, char* argv[])
{
 int *ah,*ad;
 int i,rank,bufsize=N*4;
 MPI_Status status;

 ah = (int *)malloc(N*sizeof(int));
 cudaMalloc((void **)&ad,bufsize);
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);

 if(rank == 0)
 {
  for(i=0;i<N;i++)
     ah[i]=i*5;

 cudaMemcpy(ad,ah,bufsize,cudaMemcpyHostToDevice);
 dim3 threads(1);
 dim3 grid(1);
 ckrnl<<< threads,grid >>>(ad);
// cudaMemcpy(ah,ad,bufsize,cudaMemcpyDeviceToHost);

 MPI_Send(ad,N,MPI_INT,1,100,MPI_COMM_WORLD);
}

else
{
 for(i=N-10;i<N;i++)
   printf("%2d  ",ah[i]);
 printf("\n");

 MPI_Recv(ah,N,MPI_INT,0,100,MPI_COMM_WORLD,&status);

 for(i=N-10;i<N;i++)
   printf("%2d  ",ah[i]);
 printf("\n");
}

 MPI_Finalize();
 cudaFree(ad);
 return 0;
}


