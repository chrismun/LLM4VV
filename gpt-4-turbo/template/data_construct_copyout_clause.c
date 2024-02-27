#include "acc_testsuite.h"
#ifndef T1
//T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 1024;
    int *a = (int *)malloc(n * sizeof(int));
    // Initialize array with zeros
    for(int i = 0; i < n; ++i) {
        a[i] = 0;
    }

    // Use OpenACC to modify the array in device
    #pragma acc parallel num_gangs(1) copyout(a[0:n])
    {
        int id = acc_get_thread_num();
        if(id < n) {
            a[id] = id; // Each thread writes its id to the array
        }
    }

    // Check if the changes are reflected back on the host
    for(int i = 0; i < n; ++i) {
        if(a[i] != i) {
            err++;
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