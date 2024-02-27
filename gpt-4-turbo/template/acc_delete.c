#include "acc_testsuite.h"
#ifndef T1
//T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    srand(SEED);

    // Initialize data
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
    }

    #pragma acc enter data copyin(a[0:size])
    // Intentionally leaving the region empty as we're focusing on data handling

    #pragma acc exit data delete(a[0:size])

    // Ideally, we'd check if `a` is inaccessible on the device
    // However, performing an explicit check is undefined in this context
    // Depending on the implementation, accessing `a` might lead to undefined behavior

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