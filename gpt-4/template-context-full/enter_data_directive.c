#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:enter data directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int*) malloc(N*sizeof(int));
    for(int i=0; i<N; i++) a[i] = rand()%1000;
    
    int *d_a;
    #pragma acc enter data create(d_a[0:N])
    d_a = (int*) acc_deviceptr(a);
    
    if(d_a == NULL){
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