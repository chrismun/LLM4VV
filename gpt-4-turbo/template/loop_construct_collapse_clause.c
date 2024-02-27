#include "acc_testsuite.h"
#ifndef T1
//T1: loop,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int matrix[size][size];
    int vector[size];
    int result[size] = {0};
    int host_result[size] = {0};

    // Initialize matrix and vector.
    for (int i = 0; i < size; ++i) {
      vector[i] = rand() % 100;
      for (int j = 0; j < size; ++j) {
        matrix[i][j] = rand() % 100;
      }
    }

    // Vector and matrix multiplication on host for verification.
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        host_result[i] += matrix[i][j] * vector[j];
      }
    }

    // Vector and matrix multiplication using OpenACC.
    #pragma acc data copy(matrix, vector) copyout(result)
    {
      #pragma acc parallel 
      {
        #pragma acc loop collapse(2)
        for (int i = 0; i < size; ++i) {
          for (int j = 0; j < size; ++j) {
            result[i] += matrix[i][j] * vector[j];
          }
        }
      }
    }

    // Verify the results.
    for (int i = 0; i < size; ++i) {
      if (result[i] != host_result[i]) {
        err++;
      }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}