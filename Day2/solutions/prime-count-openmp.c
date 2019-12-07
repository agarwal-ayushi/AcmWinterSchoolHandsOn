/*****************************************************************************
 Example               : omp-prime-count.c


 Objective             : Serial version of this program is giving correct result .
			 But the parallel version , implemented with OpenMP, has
			 some bug. Try to fix the issue , after studying the program.

		 	 The program's main objective is to count total number of prime
			 between a given range of numbers .

 Input                 : Number of threads and Upper-bound.
			 
			 Upper bound to find the Prime Number. By default Lower bound
			 is 1.The program finds the number of primes without Critical section
			 with Critical Section and also checks with the serial computation.

 Output                : No of Primes found between 1 to Upper-bound 
                                                                        
*********************************************************************************/
#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>

/***** User defined function for finding whether a number is prime ****/
int is_prime(int number ) 
 {
   int factor;
   int maxlimit ;
   maxlimit = sqrt(number);

   for(factor = 3;factor <= maxlimit ; factor++)
    {
     	if( number % factor != 0) 
   		continue; 
        else 
           	return 0;     //Number is not a prime
    } 
              
   return 1;  //Number is a prime
}

/* Main Program */
int main(int argc , char **argv)
{
  int *Primearray,*Check,Noofthreads,i;
  int CountD=1,Count=1,number,Maxnumber; 

/* Checking for command line arguments */
   if( argc != 3 )
    {
       printf("\t\t Very Few Arguments\n ");
       printf("\t\t Syntax : exec <Threads> <upper bound to fine prime nos.>\n");
       exit(-1);
    }

   Noofthreads=atoi(argv[1]);
   if (Noofthreads>99)
    {
       printf("\n Number of threads should be less than 100 for the execution of program. \n\n");
       exit(-1);
    }

/* Upper bound to find the prime no. */
   Maxnumber=atoi(argv[2]);
   if(Maxnumber <= 2) 
    {
      printf("\n\t\t To find the Prime number the upper bound should be greater than 2 \n ");
      exit(-1);
    }

   printf("\n\t\t Threads                        :     %d ",Noofthreads); 
   printf("\n\t\t Range to find Prime No. is     : 1 - %d ",Maxnumber);

/* Dynamic Memory Allocation */
   Primearray = (int *) malloc(sizeof(int) * Maxnumber);
   Check = (int *) malloc(sizeof(int) * Maxnumber);

/* Primearray Elements Initialization */
   for (i = 0; i < Maxnumber ; i++) 
    {
	Primearray[i] = 0  ;
        Check[i] = 0; 
    }

/* set the number of threads */
   omp_set_num_threads(Noofthreads);
 
/* OpenMP Parallel For Directive    */
#pragma omp parallel for 
   for(number =3 ; number < Maxnumber  ; number += 2)
    {
      if (is_prime(number))   
       {
	  #pragma omp critical
          {
       	  Primearray[ CountD ] = number;
          CountD++;  	 /* Data Race condition */
          }   
        }	
     }

/* Serial computation */
   for(number =3 ; number < Maxnumber  ; number += 2 )
     {
       if (is_prime(number))
        {
           Check[ Count ] = number;
           Count++;
        }
     }

  printf("\n\n\t\t Prime number calculation between [ 1 - %d ] ...........Done \n\n ",Maxnumber); 
  printf("\n\t\t The Prime No. found range [ 1 - %d ] by parallel calculation ( without critical section ) is : %d ",Maxnumber,CountD); 
  printf("\n\t\t The Prime No. found range [ 1 - %d ] by serial calculation is                                : %d ",Maxnumber,Count); 

/* Freeing Memory */
  free(Primearray);
  free(Check);

  printf("\n\n\t\t.............................................................................................\n");
 return 0;
}
