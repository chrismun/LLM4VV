#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main(){
    int failcode = 0;
    int failed;

    // Test 1: reduction clause with sum
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        int err = 0;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[10] = {0};

        #pragma acc data copyin(a[0:10])
        {
            #pragma acc kernels loop reduction(+:b[0:10])
            for (int i = 0; i < 10; ++i){
                b[i] = a[i];
            }
        }

        for (int i = 0; i < 10; ++i){
            if (fabs(b[i] - a[i]) > PRECISION){
                err += 1;
            }
        }

        if (err > 0){
            failed += 1;
        }
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    // Test 2: reduction clause with product
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        int err = 0;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[10] = {0};

        #pragma acc data copyin(a[0:10])
        {
            #pragma acc kernels loop reduction(*:b[0:10])
            for (int i = 0; i < 10; ++i){
                b[i] = a[i];
            }
        }

        for (int i = 0; i < 10; ++i){
            if (fabs(b[i] - a[i]) > PRECISION){
                err += 1;
            }
        }

        if (err > 0){
            failed += 1;
        }
    }

    if (failed != 0){
        failcode = failcode + (1 << 1);
    }

    // Test 3: reduction clause with min
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        int err = 0;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[10] = {0};

        #pragma acc data copyin(a[0:10])
        {
            #pragma acc kernels loop reduction(min:b[0:10])
            for (int i = 0; i < 10; ++i){
                b[i] = a[i];
            }
        }

        for (int i = 0; i < 10; ++i){
            if (fabs(b[i] - a[i]) > PRECISION){
                err += 1;
            }
        }

        if (err > 0){
            failed += 1;
        }
    }

    if (failed != 0){
        failcode = failcode + (1 << 2);
    }

    // Test 4: reduction clause with max
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        int err = 0;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[10] = {0};

        #pragma acc data copyin(a[0:10])
        {
            #pragma acc kernels loop reduction(max:b[0:10])
            for (int i = 0; i < 10; ++i){
                b[i] = a[i];
            }
        }

        for (int i = 0; i < 10; ++i){
            if (fabs(b[i] - a[i]) > PRECISION){
                err += 1;
            }
        }

        if (err > 0){
            failed += 1;
        }
    }

    if (failed != 0){
        failcode = failcode + (1 << 3);
    }

    return failcode;
}