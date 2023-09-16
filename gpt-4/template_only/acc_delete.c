#include "acc_testsuite.h"
#ifndef T1
// T1:acc delete, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    float *a = (float*)malloc(ARRAY_SIZE * sizeof(float));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = (float)rand() / RAND_MAX;
    }

    #pragma acc enter data copyin(a[0:ARRAY_SIZE])
    #pragma acc delete(a[0:ARRAY_SIZE])

    #pragma acc update host(a[0:ARRAY_SIZE])

    for(int i=0; i< ARRAY_SIZE; i++){
        if(a[i] != 0){
            err = 1;
            break;
        }
    }
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}