#include "acc_testsuite.h"
#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* data;
    int num_elements = 100;
    data = (int*)malloc(num_elements * sizeof(int));

    #pragma acc enter data copyin(data[0:num_elements])

    for (int i = 0; i < num_elements; i++) {
        data[i] = i;
    }

    #pragma acc exit data delete(data[0:num_elements])

    free(data);

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