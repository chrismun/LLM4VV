#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size], b[size];

    // Initializes arrays.
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = 0;
    }

    // Allocate and copy data to the device.
    #pragma acc enter data copyin(a[0:size])

    // Attempt to modify 'b' in a parallel region without explicitly mapping it.
    #pragma acc parallel loop default(present)
    for (int i = 0; i < size; ++i) {
        b[i] = a[i] + 1;
    }

    // Check for errors.
    #pragma acc exit data copyout(a[0:size])
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] + 1){
            ++err;
        }
    }

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