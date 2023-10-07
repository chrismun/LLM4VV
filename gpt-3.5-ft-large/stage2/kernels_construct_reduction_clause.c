#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int material_total = 10000000;
    int* material = (int *)malloc(material_total * sizeof(int));

    for (int x = 0; x < material_total; ++x){
        for (int y = 0; y < 4; ++y){
            if (rand() / (real_t)RAND_MAX < .9){
                material[x] += 1<<y;
            }
        }
    }

    int regions = 0;

  #pragma acc data copy(material[0:material_total])
   {
      #pragma acc kernels loop reduction(+:regions)
      for (int n = 0; n < N; ++n) {
          int total = 0;
          for (int x = 0; x < material_total; ++x) {
              for (int y = 0; y < 4; ++y) {
                  if (n / (real_t)(1<<y) == 0) {
                      total += 1<<y;
                      break;
                  }
              }
          }
          regions += total;
    }
  }

    return regions;
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