#include "acc_testsuite.h"

#ifndef T1
// T1: loop construct worker clause, V:2.7-3.3
int test1() {
    unsigned int num_workers = 128;
    int err = 0;
    srand(SEED);

    int* A = (int*)malloc(num_workers * sizeof(int));
    int sum = 0;

    for (unsigned int i = 0; i < num_workers; i++) {
        A[i] = rand() % 10;
    }

    #pragma acc parallel num_workers(num_workers)
    {
        #pragma acc loop worker reduction(+:sum)
        for (unsigned int i = 0; i < num_workers; i++) {
            sum += A[i];
        }
    }

    int check_sum = 0;
    for (unsigned int i = 0; i < num_workers; i++) {
        check_sum += A[i];
    }

    if(sum != check_sum){
        err = 1;
    }

    free(A);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}