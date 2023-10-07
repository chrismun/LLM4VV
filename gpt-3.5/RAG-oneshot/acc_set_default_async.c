#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000
#define QUEUE_SIZE 2

int main() {
    int i;
    int a[N], b[N];
    int async_val = acc_async_async0;
    int fail = 0;
    
    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }
    
    // Set default async
    acc_set_default_async(async_val);
    
    // Perform computation using async queue 0
    #pragma acc parallel loop async
    for (i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }
    
    // Sync async queue 0
    #pragma acc wait_async
    
    // Check results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            fail = 1;
            break;
        }
    }
    
    if (fail) {
        printf("Test failed\n");
    } else {
        printf("Test passed\n");
    }
    
    return 0;