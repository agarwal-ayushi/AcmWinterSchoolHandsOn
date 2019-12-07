// Compile: g++ -fopenmp problem1.cpp -o problem1
// Run: ./problem1

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

#define N (1 << 14)
const double THRESHOLD = 0.0000001;

void reference(double** A, double* x, double* y) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      y[i] = y[i] + A[i][j] * x[j];
    }
  }
}

void optimized(double** A, double* x, double* y) {
  // SB: Write your OpenMP code here
}

void check_result(double* w_ref, double* w_opt) {
  double maxdiff = 0, this_diff = 0;
  int numdiffs = 0;

  for (int i = 0; i < N; i++) {
    this_diff = w_ref[i] - w_opt[i];
    if (fabs(this_diff) > THRESHOLD) {
      numdiffs++;
      if (this_diff > maxdiff)
        maxdiff = this_diff;
    }
  }

  if (numdiffs > 0) {
    cout << numdiffs << " Diffs found over THRESHOLD " << THRESHOLD << "; Max Diff = " << maxdiff
         << endl;
  } else {
    cout << "No differences found between base and test versions\n";
  }
}

int main() {
  std::cout << std::fixed;
  std::cout << std::setprecision(5);

  double* x = new double[N];
  double* y_ser = new double[N];
  double* y_omp = new double[N];

  for (int i = 0; i < N; i++) {
    x[i] = 1.0;
    y_ser[i] = 1.0;
    y_omp[i] = 1.0;
  }

  double** A = new double*[N];
  for (int i = 0; i < N; i++) {
    A[i] = new double[N];
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = i + j;
    }
  }

  double start = omp_get_wtime();
  reference(A, x, y_ser);
  double end = omp_get_wtime();
  cout << "Time for reference version: " << end - start << " seconds\n";

  start = omp_get_wtime();
  optimized(A, x, y_omp);
  end = omp_get_wtime();
  check_result(y_ser, y_omp);
  cout << "Time for OpenMP version: " << end - start << " seconds\n";

  return EXIT_SUCCESS;
}
