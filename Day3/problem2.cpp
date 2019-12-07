// Compile: g++ -fopenmp problem2.cpp -o problem2
// Run: ./problem2

#include <cassert>
#include <iomanip>
#include <iostream>
#include <omp.h>

#define N 40
#define THRESHOLD 20

using namespace std;

long ser_fib(int n) {
  if (n == 0 || n == 1) {
    return (n);
  }
  return ser_fib(n - 1) + ser_fib(n - 2);
}

long omp_fib(int n) {
  // SB: Write your OpenMP code here
}

int main(int argc, char** argv) {
  std::cout << std::fixed;
  std::cout << std::setprecision(5);

  double start, end;

  start = omp_get_wtime();
  long s_fib = ser_fib(N);
  end = omp_get_wtime();
  cout << "Serial time: " << (end - start) << " seconds\n";

  start = omp_get_wtime();
  long v1_fib = omp_fib(N);
  end = omp_get_wtime();
  assert(s_fib == v1_fib);
  cout << "OMP Version time: " << (end - start) << " seconds\n";

  return EXIT_SUCCESS;
}
