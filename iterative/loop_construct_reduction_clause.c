#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *arr = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    int sum = 0;
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < N; i++) {
        sum += arr[i];
    }

    int expected_sum = 0;
    for(int i = 0; i < N; i++) {
        expected_sum += arr[i];
    }

    if(sum != expected_sum) {
        err++;
        printf("Error: sum is not correct. Expected %d, got %d\n", expected_sum, sum);
    }

    free(arr);

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