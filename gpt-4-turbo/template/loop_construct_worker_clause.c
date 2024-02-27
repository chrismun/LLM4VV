#include "acc_testsuite.h"
#ifndef T1
// T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size*sizeof(int));
    int *b = (int*)malloc(size*sizeof(int));
    int reduced_sum = 0, calculated_sum = 0;

    // Populate an array with random values
    for (int i = 0; i < size; ++i){
        a[i] = rand() / (RAND_MAX / 100);
    }

    #pragma acc parallel num_workers(4) copy(a[0:size],b[0:size])
    {
        #pragma acc loop worker reduction(+:reduced_sum)
        for(int i = 0; i < size; ++i){
            b[i] = a[i] * 2;
            reduced_sum += a[i];
        }
    }

    // Check that work was divided among workers and reduction was properly applied.
    for(int i = 0; i < size; ++i){
        calculated_sum += a[i];
        if(b[i] != a[i] * 2){
            err += 1;
        }
    }

    if (calculated_sum != reduced_sum) {
        err += 1;
    }

    free(a);
    free(b);

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