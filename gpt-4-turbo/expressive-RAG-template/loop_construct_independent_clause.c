#include <stdlib.h>
#include <stdio.h>

// Using the given template naming conventions for checks
#ifndef T1
// T1: loop construct independent clause, V:2.7-3.3
int test1(){
    int err = 0;
    int n = 100; // Number of elements in the array
    int a[n];
    int expected = 5; // Expected value after modification

    // Initialize array
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }

    // OpenACC parallel loop to modify the array
    // This loop is treated as independent by default
    #pragma acc parallel loop
    for (int i = 0; i < n; ++i) {
        a[i] = expected; // Independent modification
    }

    // Verification: check if modifications were made correctly
    for (int i = 0; i < n; ++i) {
        if (a[i] != expected) {
            err = 1; // Error if any element does not match expected value
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}