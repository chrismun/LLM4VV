#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int array[100];
    int host_result = 0;
    for (int x = 0; x < 100; ++x) {
        array[x] = rand() % 100;
        host_result += array[x];
    }

    #pragma acc serial reduction(+:host_result)
    {
        for (int x = 0; x < 100; ++x) {
            host_result += array[x];
        }
    }

    int device_result = 0;
    #pragma acc parallel copy(array[0:100]) reduction(+:device_result)
    {
        for (int x = 0; x < 100; ++x) {
            device_result += array[x];
        }
    }

    if (host_result != device_result) {
        err = 1;
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