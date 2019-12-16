#include <stdio.h>
#define N (65536*2048)
#define TPB 512

__global__ void mykernel(int *da, int *db, int *dc) {
	int index=threadIdx.x+blockIdx.x*blockDim.x;
	dc[index] = da[index]+db[index];
}
int main(void)
{
	int *a = new int [N]; 
	int *b = new int [N];
	int *c = new int [N];
	int *da, *db, *dc;
	int size = sizeof(int);
	
	for (int i=0; i < N; i++) {
		a[i]=i;
		b[i]=i+1;
	}
	cudaMalloc((void **)&da, size*N);
	cudaMalloc((void **)&db, size*N);
	cudaMalloc((void **)&dc, size*N);

	cudaMemcpy(da, a, size*N, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, size*N, cudaMemcpyHostToDevice);
	int M = N/TPB;
	mykernel<<<M, TPB>>>(da, db, dc);

	cudaMemcpy(c, dc, size*N, cudaMemcpyDeviceToHost);
	//printf("hellow World!");
	for (int i=0; i < 10; i++){
		//printf("%d\t", c[i]);
	}
	free(a); free(b); free(c);
	cudaFree(da); cudaFree(db); cudaFree(dc);
	return 0;
}
