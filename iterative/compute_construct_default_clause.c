#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *data = (int*)malloc(N * sizeof(int));
    int sum = 0;

    for (int i = 0; i < N; ++i) {
        data[i] = rand() % 100;
    }

    #pragma acc data copyin(data[0:N])
    {
        #pragma acc parallel loop default(present)
        for (int i = 0; i < N; ++i) {
            sum += data[i];
        }
    }

    int expected_sum = 0;
    for (int i = 0; i < N; ++i) {
        expected_sum += data[i];
    }

    if (sum != expected_sum) {
        err++;
        printf("Expected sum: %d, Computed sum: %d\n", expected_sum, sum);
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