//Module(s) to be loaded
//module load pgi/19.4
//compilation:
//pgcc -acc -fast -Minfo=all -ta=tesla:managed -Mprof=ccff laplace_acc.c
//execution:./a.out


#include <stdio.h>
#include <string.h>
#include <math.h>

#define ITER_MAX 50
#define N 5000

// Prints every N/10th row and column of the matrix
void printGrid(double A[N][N]) {
	
	int i, j;

	for (i = 0; i < N; i+=(N/10)) {
		for (j = 0; j < N; j+=(N/10))
			printf("%lg\t", A[i][j]);
		printf("\n");
	}
}

int main (int argc, char *argv[]) {

	int i, j, iter = 0;
	double A[N][N], Anew[N][N], test=0;

	//Clear out array contents with 0
	//memset(A, 0, sizeof(double) * N * N);
	//memset(Anew, 0, sizeof(double) * N * N);

	//#pragma acc data create(A,Anew) 
	{
	//Heat left and right side of grid
	for (i = 0; i < N; ++i) {
		A[i][0] = 100;
		A[i][N-1] = 100;
	}

	//printGrid(A);
//	#pragma acc data copy(A) create(Anew)
	// Proceed until ITER_MAX iterations are complete
	while (iter < ITER_MAX) {

		#pragma acc kernels loop gang(32), vector(16)
		//Compute heat flow
		for (i = 1; i < N - 1; i++)
		#pragma acc loop gang(16) vector(32)
			for (j = 1; j < N - 1; j++)
				//Anew[i][j] = 0.25 * (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
				Anew[i][j] = tanf(exp(sinf(cosf(sinf(cosf(0.25 * (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1])))))));
		#pragma acc kernels loop 
		//Copy new array to old
		for (i = 1; i < N - 1; i++)
		#pragma acc loop gang(16) vector(32)
        	        for (j = 1; j < N - 1; j++)
				A[i][j] = Anew[i][j];
	
		iter++;
	}
//	test = A[100][100];
	}

//	printGrid(A);
	printf("%f\n", A[N-1][N-1]);

	return 0;
}
