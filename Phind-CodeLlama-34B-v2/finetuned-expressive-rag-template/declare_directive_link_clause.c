#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    a = (int *)malloc(10 * sizeof(int));
    int *d_a;

    #pragma acc enter data copyin(a[0:10])
    #pragma acc declare link(a[0:10])

    #pragma acc parallel present(a[0:10])
    {
        int i = acc_thread_id();
        a[i] = i;
    }

    #pragma acc exit data copyout(a[0:10])
    #pragma acc exit data delete(a[0:10])

    for (int i = 0; i < 10; i++) {
        if (a[i] != i) {
            err = 1;
            break;
        }
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