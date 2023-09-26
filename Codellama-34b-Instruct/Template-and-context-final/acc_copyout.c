c
#include "acc_testsuite.h"

#ifndef T1
//T1:acc copyout,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test 1: The data section is in shared memory.
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    acc_copyout(data, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }
    free(data);

    // Test 2: The dynamic reference counter for the data section is zero.
    int *data2 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data2[i] = i;
    }
    acc_copyout(data2, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data2[i] != i) {
            err = 1;
            break;
        }
    }
    free(data2);

    // Test 3: The data section is not in shared memory and is not present in the current device memory.
    int *data3 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data3[i] = i;
    }
    acc_copyout(data3, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data3[i] != i) {
            err = 1;
            break;
        }
    }
    free(data3);

    // Test 4: The data section is an array section that is not contiguous (in Fortran).
    int *data4 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data4[i] = i;
    }
    acc_copyout(data4, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data4[i] != i) {
            err = 1;
            break;
        }
    }
    free(data4);

    // Test 5: Part of the data section is already present in the current device memory but all of the data section is not.
    int *data5 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data5[i] = i;
    }
    acc_copyout(data5, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data5[i] != i) {
            err = 1;
            break;
        }
    }
    free(data5);

    // Test 6: The async_arg argument is not a valid async-argument value.
    int *data6 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data6[i] = i;
    }
    acc_copyout(data6, sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        if (data6[i] != i) {
            err = 1;
            break;
        }
    }
    free(data6);

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