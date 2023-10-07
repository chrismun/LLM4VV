#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Test acc_copyin behavior
    int *data = (int*)malloc(N * sizeof(int));
    int *copy = (int*)acc_copyin(data, N * sizeof(int));
    if (copy != data) {
        err = 1;
    }

    free(data);
    acc_delete(copy);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}