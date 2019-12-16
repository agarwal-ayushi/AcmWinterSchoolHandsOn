The directory contains a few sample programs,whose compilation and execution 
instructions are described in the beiginning of the respective files.

(1). mm-blas.cu    - CUDA Matrix Multiplication program using the CuBlas library.
(2). cumpi.cu      - CUDA aware MPI program.
(3). laplace_acc.c - OpenACC version of the basic stencil problem.

Module(s) required:

CUDA:
====
        Setting up of environment:
                module load cuda/10.1
        compilation:
                nvcc <<prog_name.cu>>
        Execution:
                ./a.out
OpenACC:
=======
        Setting up of environment:
                module load pgi/19.4
        Compilation:
                pgcc -acc -fast -Minfo=all -ta=tesla:managed -Mprof=ccff <<prog+name.c>>
        Execution:
                ./a.out

CUDA-MPI:
========
        Setting up of environment:
        	module load cuda/10.1
        	module load pgi/openmpi/3.1.3/2019
        Compilation:
                nvcc cumpi.cu -I/opt/pgi/linux86-64-llvm/19.4/mpi/openmpi-3.1.3/include -L/opt/pgi/linux86-64-llvm/19.4/mpi/openmpi-3.1.3/lib -lmpi
        Execution:
                mpirun -n 2 ./a.out

