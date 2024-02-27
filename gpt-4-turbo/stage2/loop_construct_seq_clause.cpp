#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#ifndef ACC_TESTSUITE_H
#define ACC_TESTSUITE_H
#define SEED 12345
#define NUM_TEST_CALLS 10

// Utility to check OpenACC runtime version for completeness; not essential for this test
void check_openacc_version(){
    int major, minor;
    acc_get_property(0, acc_device_not_host, acc_property_major_version, &major);
    acc_get_property(0, acc_device_not_host, acc_property_minor_version, &minor);
    std::cout << "Running with OpenACC Version: " << major << "." << minor << std::endl;
}

#endif // ACC_TESTSUITE_H

#ifndef T1
// T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int data[size];
    
    // Initialize data to 0
    for (int i = 0; i < size; ++i){
        data[i] = 0;
    }
    
    // Expected outcome: data[i] = i
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop seq
        for (int i = 0; i < size; ++i){
            data[i] = i;
        }
    }
    
    // Validate sequential execution
    for (int i = 0; i < size; ++i){
        if(data[i] != i){
            err++;
        }
    }

    return err;
}
#endif

int main(){
    check_openacc_version();  // Optional: Confirm OpenACC API version
    
    int failcode = 0;
    int failed = 0;
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