#include <iostream>
#include <openacc.h>
#include <cstdlib>

#ifndef T1
// T1: loop construct private clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // Seed for repeatability
    
    const int size = 10;
    int original_var = 42; // This variable should remain unchanged outside the parallel region
    
    #pragma acc parallel num_gangs(1)
    {
        int array[size];
        // Initialize array within parallel region
        #pragma acc loop private(original_var)
        for (int i = 0; i < size; ++i) {
            original_var = rand() % 100; // Modify the private instance
            array[i] = original_var; // Just to use the private var, avoiding optimization out
        }
        // If original_var was correctly treated as private, its initial value should be unchanged here
    }
    
    // Verify if original_var remains unchanged
    if(original_var != 42) {
        err += 1; // Indicates the private clause did not work as expected
    }
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

    #ifndef T1
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    #endif

    return failcode;
}