#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 123
#define n 1024
#define NUM_TEST_CALLS 10
#define PRECISION 1e-5
#define NUM_WORKERS 4

typedef float real_t;

int test_num_workers(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *worker_results = (real_t *)calloc(NUM_WORKERS, sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel num_workers(NUM_WORKERS) copyout(b[0:n])
        {
            #pragma acc loop worker reduction(+:worker_results[:NUM_WORKERS])
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
                worker_results[acc_get_worker_num()] += a[x];
            }
        }
    }

    real_t sum_check = 0;
    for (int i = 0; i < NUM_WORKERS; ++i) {
        sum_check += worker_results[i];
    }

    real_t array_sum = 0;
    for (int x = 0; x < n; ++x){
        array_sum += a[x];
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }
    
    // Verify that the calculated sum using workers matches the total sum of array elements
    if (fabs(sum_check - array_sum) > PRECISION * n) {
        err += 1;
    }

    free(a);
    free(b);
    free(worker_results);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_num_workers();
    }
    if (failed != 0){
        failcode = 1; // Indicates test failure
    }
    
    if(failcode == 0) {
        printf("PASS: num_workers test passed.\n");
    } else {
        printf("FAIL: num_workers test failed.\n");
    }
    
    return failcode;
}