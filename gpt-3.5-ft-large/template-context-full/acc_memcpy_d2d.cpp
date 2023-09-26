#include "acc_testsuite.h"
#ifndef T1
//T1: acc_memcpy_d2d,V:2.7-3.3
int test1() {
  int err = 0;
  srand(SEED);
  real_t *host_data = (real_t *)malloc(LOOP_COUNT * PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *host_data_copy = (real_t *)malloc(LOOP_COUNT * PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *a = (real_t *)malloc(PRESENT_HOST_ALLOCATION * sizeof(real_t));
  real_t *a_devcopy = (real_t *)malloc(PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *a_hostcopy = (real_t *)malloc(PRESENT_HOST_ALLOCATION *
sizeof(real_t));

  for (int x = 0; x < LOOP_COUNT; ++x) {
    for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
      host_data[x * PRESENT_HOST_ALLOCATION + y] = rand() / (real_t)(RAND_MAX /
10);
      host_data_copy[x * PRESENT_HOST_ALLOCATION + y] =
host_data[x * PRESENT_HOST_ALLOCATION + y];
    }
    acc_copyin(&host_data[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
  }


  #pragma acc data copyout(host_data[0:LOOP_COUNT * PRESENT_HOST_ALLOCATION])
  {
  #pragma acc parallel 
  {
    #pragma acc loop
    for (int x = 0; x < LOOP_COUNT; ++x) {
      for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
        host_data[x * PRESENT_HOST_ALLOCATION + y] += 1;
      }
    }
   }
  }

  for (int x = 0; x < LOOP_COUNT; ++x) {
    acc_memcpy_d2h(a, &host_data[x * PRESENT_HOST_ALLOCATION * sizeof(real_t)],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
    #pragma acc parallel
    {
      #pragma acc loop
      for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
        a[y] += 1;
      }
    }
    acc_memcpy_h2d(&host_data[x * PRESENT_HOST_ALLOCATION * sizeof(real_t)], a,
PRESENT_HOST_ALLOCATION * sizeof(real_t));
    #pragma acc exit data copyout(host_data[x * PRESENT_HOST_ALLOCATION:
PRESENT_HOST_ALLOCATION])
  }
    
  return err;
}
#endif

#ifndef T2
//T2: acc_memcpy_d2d, data,V:2.7-3.3
int test2() {
  int err = 0;
  srand(SEED);
  real_t *host_data = (real_t *)malloc(LOOP_COUNT * PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *host_data_copy = (real_t *)malloc(LOOP_COUNT * PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *a = (real_t *)malloc(PRESENT_HOST_ALLOCATION * sizeof(real_t));
  real_t *a_devcopy = (real_t *)malloc(PRESENT_HOST_ALLOCATION *
sizeof(real_t));
  real_t *a_hostcopy = (real_t *)malloc(PRESENT_HOST_ALLOCATION *
sizeof(real_t));

  for (int x = 0; x < LOOP_COUNT; ++x) {
    for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
      host_data[x * PRESENT_HOST_ALLOCATION + y] = rand() / (real_t)(RAND_MAX /
10);
      host_data_copy[x * PRESENT_HOST_ALLOCATION + y] =
host_data[x * PRESENT_HOST_ALLOCATION + y];
    }
    acc_copyin(&host_data[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
  }

  #pragma acc data copyout(host_data[0:LOOP_COUNT * PRESENT_HOST_ALLOCATION])
  {
    for (int x = 0; x < LOOP_COUNT; ++x) {
      acc_attach((void *)&host_data[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
      acc_attach((void *)&host_data_copy[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
      #pragma acc enter data copyin(a[0:PRESENT_HOST_ALLOCATION])
      for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
        a[y] = 1;
      }
      acc_memcpy_h2d(a, &host_data[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
      #pragma acc parallel
      {
        #pragma acc loop
        for (int y = 0; y < PRESENT_HOST_ALLOCATION; ++y) {
          a[y] += 1;
        }
      }
      acc_memcpy_d2h(&host_data[x * PRESENT_HOST_ALLOCATION],
a, PRESENT_HOST_ALLOCATION * sizeof(real_t));
      #pragma acc exit data copyout(a[0:PRESENT_HOST_ALLOCATION])
      acc_detach((void *)&host_data[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t));
      acc_detach((void *)&host_data_copy[x * PRESENT_HOST_ALLOCATION],
PRESENT_HOST_ALLOCATION * sizeof(real_t)));
    }
  }

  for (int x = 0; x < LOOP_COUNT * PRESENT_HOST_ALLOCATION; ++x) {
    if (fabs(host_data_copy[x] - host_data[x]) > PRECISION) {
      err += 1;
      break;
    }
  }

  return err;
}
#endif

int main() {
  int failcode = 0;
  int failed;
#ifndef T1
  failed = 0;
  for (int x = 0; x < NUM_TEST_CALLS; ++x) {
    failed = failed + test1();
  }
  if (failed != 0) {
    failcode = failcode + (1 << 0);
  }
#endif
#ifndef T2
  failed = 0;
  for (int x = 0; x < NUM_TEST_CALLS; ++x) {
    failed = failed + test2();
  }
  if (failed != 0) {
    failcode = failcode + (1 << 1);
  }
#endif
  return failcode;
}