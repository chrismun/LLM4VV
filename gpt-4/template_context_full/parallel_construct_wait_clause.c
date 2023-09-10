#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:parallel construct wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int h_a = rand();
    int * d_a = (int *) acc_malloc(sizeof(int));
    
    #pragma acc data copyin(h_a) copyout(d_a[0:1]) async(1)
    #pragma acc parallel present(h_a, d_a[0:1]) async(1)
    {
          d_a[0] = h_a; 
    }
  
    #pragma acc wait(1)

    if (d_a[0] != h_a){
        err = 1;
    }
    
    acc_free(d_a);
    
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