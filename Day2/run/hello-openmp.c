
/*****************************************************************************
 Objective             : OpenMP program to print "Hello World"
                         This example demonstrates the use of
			 omp_set_num_threads()
                         omp_get_thread_num()
                         omp_get_num_threads() calls
				and
			 num_threads() clause

Input                 : Set the number of threads to use by means of the follwoing and,
                        see which construct has higher priority:
			1. OMP_NUM_THREADS environment variable (export OMP_NUM_THREADS=4)
			2. uncommenting omp_set_num_threads() call
			3. uncommenting num_threads() clause	


 Output                : Each thread prints a message "Hello World" and its
                         rank.
*********************************************************************************/


#include <stdio.h>
#include "omp.h"

main()
{
	int Threadid, Noofthreads;

        //omp_set_num_threads(4); 
#pragma omp parallel private(Threadid) //num_threads(3)
	{
		Threadid = omp_get_thread_num();
		printf("\nHello World by threadid %d\n", Threadid);
		#pragma omp barrier
		/* Master Thread Has Its Threadid 0 */
		if (Threadid == 0) 
         	 {
			Noofthreads = omp_get_num_threads();
			printf("Master thread prints total number of threads for this execution are %d\n", Noofthreads);
		}
	}

}
