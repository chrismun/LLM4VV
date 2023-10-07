#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef T1
/*T1:loop construct collapse clause,V:2.0-2.7*/

#define N 100

float a[N][N];

int test1() {
    int err = 0;
    srand(time(NULL));

    // Fill the array with random numbers
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = rand() % 100; // Random numbers between 0 and 99
        }
    }

    // Calculate the sum of all elements on the device using OpenACC
    float acc_sum = 0.0;
    #pragma acc parallel loop collapse(2) reduction(+:acc_sum)
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            acc_sum += a[i][j];
        }
    }

    // Calculate the sum of all elements on the host
    float host_sum = 0.0;
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            host_sum += a[i][j];
        }
    }

    // Compare the results
    if(fabs(acc_sum - host_sum) > 1E-5) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}
#endif