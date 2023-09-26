#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

//T1:acc unmap data,V:2.7-3.0
int test1() {
  int err = 0;
  srand(SEED);

  float *hostData = (float*)malloc(100*sizeof(float));
  // Initialize with random values
  for(int i=0; i<100; i++) {
      hostData[i] = (float) rand();
  }
  acc_map_data(hostData, 100 * sizeof(float));
  
  if(acc_is_present(hostData, 100 * sizeof(float)) == 0) {
      err = 1;
  }
  
  acc_unmap_data(hostData);
  if(acc_is_present(hostData, 100 * sizeof(float)) != 0) {
      err += 1;
  }

  free(hostData);

  return err;
}

int main() {
  int failcode = 0;
  int failed = 0;
  for (int x = 0; x < NUM_TEST_CALLS; ++x) {
      failed = failed + test1();
  }
  if (failed != 0){
      failcode = failcode + (1 << 0);
  }
  return failcode;
}