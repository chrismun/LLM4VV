#include "acc_testsuite.h"

#ifndef T1
#define T1 1
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *data = (int*)malloc(n * sizeof(int));
    int sum = 0;

    for (int i = 0; i < n; ++i){
        data[i] = rand() % 100;
    }

    #pragma acc data copy(data[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            sum += data[i];
        }

        #pragma acc wait
        printf("Sum: %d\n", sum);
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