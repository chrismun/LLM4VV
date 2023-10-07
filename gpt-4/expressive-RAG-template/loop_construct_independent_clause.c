#include "acc_testsuite.h"
#include <stdlib.h>

// T1: Testing OpenACC loop construct independent clause, Version: 2.7-3.3
int test1(){
    int err = 0;
    int n = 10000;

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    
    srand(SEED);

    for(int i=0; i<n; i++) {
      a[i] = rand() % 1000;
      b[i] = 0;
    }

    #pragma acc parallel loop independent
    for(int i=0; i<n; i++) {
      b[i] = a[i];
    }

    for(int i=0; i<n; i++) {
      if(a[i] != b[i]) err = 1;
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}