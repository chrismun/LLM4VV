#include "acc_testsuite.h"
#ifndef T1
//T1:{data_management},V:2.7-3.3
int test1(){
    int err = 0;
    int *a_host;
    int *a_device;
    int n = 1024; // or any size you prefer
    srand(SEED);

    a_host = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        a_host[i] = rand() / (RAND_MAX / 100);
    }

    // Explicitly allocate device memory and copy data
    #pragma acc enter data create(a_device[0:n])
    #pragma acc parallel loop copyin(a_host[0:n]) copyout(a_device[0:n])
    for (int i = 0; i < n; ++i) {
        a_device[i] = a_host[i] + 1;
    }

    // Unmapping device data
    #pragma acc exit data copyout(a_host[0:n]) delete(a_device[0:n])
  
    // Testing if modifications are reflected correctly on the host
    for (int i = 0; i < n; ++i) {
        if (a_host[i] != i + 1) { // Considering the initialized values and modifications
            err++;
        }
    }

    free(a_host);

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