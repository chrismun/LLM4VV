#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
/*T1:parallel construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int aSize = 1024;
    int *a = (int*) malloc(sizeof(int) * aSize);
    int total = 0;
    int acc_total = 0;

    // Generating random data
    for (int i = 0; i < aSize; ++i) {
        a[i] = rand() % 1000;
        total += a[i];
    }

    // Parallel compute using OpenACC
    #pragma acc parallel num_gangs(128) vector_length(128) copyin(a[0:aSize]) reduction(+:acc_total)
    {
          #pragma acc loop gang vector reduction(+:acc_total)
          for (int i = 0; i < aSize; ++i) {
              acc_total += a[i];
          }
    }

    if (total != acc_total){
        err = 1;
    }

    free(a);
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