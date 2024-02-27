#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int a[size];
    int private_vals[size];

    // Initialize array with random data
    for(int i = 0; i < size; i++){
        a[i] = rand() % 100;
        private_vals[i] = 0; // Initialize private_vals with 0
    }

    // Use OpenACC parallel directive with private clause
    #pragma acc parallel num_gangs(1) vector_length(size) copy(a) private(private_vals)
    {
        int gang = omp_get_team_num(); // Assuming OpenMP 4.5 or newer for demonstration; replace with your method to obtain gang ID as per your OpenACC environment
        for(int i = 0; i < size; i++){
            private_vals[i] = a[i] + gang; // Every thread modifies its own private copy
        }
    }

    // Verification - in this simplistic test, we only check if 'private_vals' remain unchanged (still 0) outside the parallel region
    // which indicates that the private clause worked properly.
    for (int i = 0; i < size; i++) {
        if (private_vals[i] != 0) {
            err++;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}