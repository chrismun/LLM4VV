#include "acc_testsuite.h"

#ifndef T1
#define T1 1
int test1(){
    int err = 0;
    srand(SEED);

    int N = 10000;
    int *data = (int*)malloc(N * sizeof(int));
    int sum = 0;

    // Initialize data
    for(int i = 0; i < N; i++){
        data[i] = rand() % 100;
    }

    // Compute sum
    #pragma acc parallel loop copyin(data[0:N]) copyout(sum) wait
    for(int i = 0; i < N; i++){
        sum += data[i];
    }

    // Check sum
    int expected_sum = 0;
    for(int i = 0; i < N; i++){
        expected_sum += data[i];
    }

    if(sum != expected_sum){
        err++;
        printf("Error: sum is %d, expected %d\n", sum, expected_sum);
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