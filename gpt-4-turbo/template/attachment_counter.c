#include "acc_testsuite.h"
#ifndef T1
// T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1000;
    int *data = (int*)malloc(size * sizeof(int));
    int *counter = (int*)malloc(size * sizeof(int));
    // Initialize data with random values
    for (int i = 0; i < size; ++i){
        data[i] = rand() % 10; // Random values between 0 and 9
        counter[i] = 0;
    }

    #pragma acc parallel loop copyin(data[0:size]) copyout(counter[0:size])
    for (int i = 0; i < size; ++i){
        int count = 0;
        for (int j = 0; j < size; ++j){
            if (data[j] == data[i])
                count++;
        }
        counter[i] = count - 1; // -1 to exclude self-counting
    }

    // Verification
    for (int i = 0; i < size; ++i){
        int expected_count = -1;
        for (int j = 0; j < size; ++j){
            if (data[j] == data[i])
                expected_count++;
        }
        if (counter[i] != expected_count){
            err++;
        }
    }

    free(data);
    free(counter);

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