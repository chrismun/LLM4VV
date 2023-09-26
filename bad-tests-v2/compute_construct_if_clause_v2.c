#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: if clause with true condition
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = rand() % 256;
        int b = rand() % 256;
        int c = 0;

        #pragma acc data copyin(a, b) copyout(c)
        {
            #pragma acc kernels if(a > b)
            {
                c = a + b;
            }
        }

        if (c != a + b) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: if clause with false condition
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = rand() % 256;
        int b = rand() % 256;
        int c = 0;

        #pragma acc data copyin(a, b) copyout(c)
        {
            #pragma acc kernels if(a < b)
            {
                c = a + b;
            }
        }

        if (c != 0) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}