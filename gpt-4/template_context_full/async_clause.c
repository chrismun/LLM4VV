#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:async clause,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(N*sizeof(int));
    int *d_a;
    d_a = (int*)acc_malloc(N*sizeof(int));

    for(int i=0; i<N; i++){
        a[i]=rand()%N;
    }

    #pragma acc enter data create(d_a[0:N])
    #pragma acc parallel loop async
    for(int i=0; i<N; i++){
        d_a[i]=a[i]*a[i];
    }

    #pragma acc exit data copyout(d_a[0:N]) async 

    acc_wait_all();

    for(int i=0; i<N; i++){
        if(d_a[i] != a[i]*a[i]){
            err = 1;
        }
    }

    acc_free(d_a);
    free(a);

    return err;
}
#endif

int main() {
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