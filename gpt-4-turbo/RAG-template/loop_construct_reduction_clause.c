#include "acc_testsuite.h"
#ifndef T1
// T1:{loop},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int N = 1024;
    int sum = 0;
    int *data = (int *)malloc(N * sizeof(int));

    // Initialize data with random numbers
    for (int i = 0; i < N; ++i) {
        data[i] = rand() % 100;  // Random numbers between 0 and 99
    }

    #pragma acc parallel num_gangs(1) copy(data[0:N]) reduction(+:sum)
    {
        #pragma acc loop
        for (int i = 0; i < N; ++i) {
            sum += data[i];
        }
    }

    // Validate the results
    int host_sum = 0;
    for (int i = 0; i < N; ++i) {
        host_sum += data[i];
    }

    if (host_sum != sum) {
        err += 1;
    }

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