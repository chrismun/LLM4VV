#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: if clause with false condition
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int *a = (int *)malloc(sizeof(int));
        int *b = (int *)malloc(sizeof(int));

        *a = 1;
        *b = 0;

        #pragma acc host_data if(0)
        {
            #pragma acc kernels
            {
                #pragma acc loop
                for (int i = 0; i < 10; ++i) {
                    b[i] = a[i];
                }
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (b[i] != a[i]) {
                failed++;
            }
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: if clause with true condition
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int *a = (int *)malloc(sizeof(int));
        int *b = (int *)malloc(sizeof(int));

        *a = 1;
        *b = 0;

        #pragma acc host_data if(1)
        {
            #pragma acc kernels
            {
                #pragma acc loop
                for (int i = 0; i < 10; ++i) {
                    b[i] = a[i];
                }
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (b[i] != a[i]) {
                failed++;
            }
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}