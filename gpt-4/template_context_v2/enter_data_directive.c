#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 100;
    int*a = (int*)malloc(N*sizeof(int));
    int*b = (int*)malloc(N*sizeof(int));
    for(int i=0; i<N; i++){
        a[i] = rand();
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc parallel loop copyout(b[0:N])
    for(int i=0; i<N; i++){
        b[i] = a[i];
    }
    #pragma acc exit data delete(a[0:N])
    
    for(int i=0; i<N; i++){
        if(b[i] != a[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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