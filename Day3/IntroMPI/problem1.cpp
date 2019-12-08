#include <stdio.h>
#include <iostream>
#include <mpi.h>

int pRank=0;
int pNum=0;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pRank);
	MPI_Comm_size(MPI_COMM_WORLD, &pNum);
	
	MPI_Status statusO, statusE;
//	std::cout << "Hello";
	if (pRank % 2 != 0 && pRank != 1) MPI_Send(&pRank, 1, MPI_INT, 1, pRank%2, MPI_COMM_WORLD);
	if (pRank == 1) {
		int sumOdd=1;
		int tempO;
		for (int i=1; i < pNum/2; i++) {
			MPI_Recv(&tempO, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &statusO);
			//std::cout << tempO << "\t";
			sumOdd+=tempO;
		}
		std::cout << "Odd Rank Sum =\t" << sumOdd << "\n";
	}
	if (pRank % 2 == 0 && pRank !=0) MPI_Send(&pRank, 1, MPI_INT, 0, pRank%2, MPI_COMM_WORLD);
	if (pRank == 0) {
		int sumEven=0, tempE=0;
		for (int i=1; i < pNum/2; i++) {
			MPI_Recv(&tempE, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &statusE);
			sumEven+=tempE; 
		}
		std::cout << "Even Rank Sum=\t" << sumEven << "\n";
	}
	MPI_Finalize();
	return 0;
}

