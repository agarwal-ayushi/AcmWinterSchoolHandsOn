# $rows and $cols and $proc would be from ENV variables.
# Please make sure you've set the ENV variables on the terminal running the scripts
rm -rf results/results_openmp_rowM.txt
{
  echo "Row-Wise Striped Matrix-Vector Multiplication with OpenMP\n"
  export OMP_NUM_THREADS=1
  echo "\nOMP_NUM_THREADS =1"
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =2"
  export OMP_NUM_THREADS=2
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =3"
  export OMP_NUM_THREADS=3
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =4"
  export OMP_NUM_THREADS=4
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =8"
  export OMP_NUM_THREADS=8
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =16"
  export OMP_NUM_THREADS=16
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =20"
  export OMP_NUM_THREADS=20
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =24"
  export OMP_NUM_THREADS=24
  ./problem1_rowM 
  echo "\nOMP_NUM_THREADS =40"
  export OMP_NUM_THREADS=40
  ./problem1_rowM 
} > results/results_openmp_rowM.txt
