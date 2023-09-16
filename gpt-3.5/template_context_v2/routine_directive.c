#include "acc_testsuite.h"
#ifndef T1
#define N 1000

//T1:routine directive,V:2.7-3.3
void saxpy(int n, float a, float *x, float *y) {
  #pragma acc routine(block)                 // Specify routine directive
  for (int i = 0; i < n; ++i) {
    y[i] = a * x[i] + y[i];
  }
}

int saxpy_check(float *x, float *y, float *res, int n, float a) {
  for (int i = 0; i < n; ++i) {
    if (res[i] != a * x[i] + y[i]) {
      return 1;   // Return non-zero on test failure
    }
  }
  return 0;       // Return zero on test success
}

int test1() {
  int err = 0;
  srand(SEED);

  float x[N];
  float y[N];
  float res[N];
  float a = rand() / (float)RAND_MAX;

  // Initialize arrays
  for (int i = 0; i < N; ++i) {
    x[i] = rand() / (float)RAND_MAX;
    y[i] = rand() / (float)RAND_MAX;
    res[i] = y[i];      // Make a copy of y
  }

  // Call saxpy routine
  saxpy(N, a, x, y);

  // Check result
  err = saxpy_check(x, res, y, N, a);

  return err;
}
#endif

int main() {
  int failcode = 0;
  int failed;
#ifndef T1
  failed = 0;
  for (int x = 0; x < NUM_TEST_CALLS; ++x) {
    failed += test1();
  }
  if (failed != 0) {
    failcode += (1 << 0);
  }
#endif
  return failcode;
}