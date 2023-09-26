#include <openacc.h>
#include <stdlib.h>
#include "acc_testsuite.h"

int test_host_data_if_clause(){
    int err = 0;
    float *a, *b, *c;
    int length = 1024;
    a = (float*) malloc (length * sizeof(float));
    b = (float*) malloc (length * sizeof(float));
    c = (float*) malloc (length * sizeof(float));

    // Initialize the arrays
    for (int i = 0; i < length; i++) {
        a[i] = (float)i;
        b[i] = (float)i;
        c[i] = 0.f;
    }

    // Check if the device is present
    int is_device_present = acc_get_num_devices(acc_device_default);
  
    //host_data if clause will only move the data to device if the device is present
    #pragma acc host_data use_device(a, b, c) if(is_device_present)
    {
        #pragma acc parallel loop num_gangs(256)
        for (int i = 0; i < length; i++) {
            c[i] = a[i] + b[i];
        }
    }
  
    // Check the results
    for (int i = 0; i < length; i++) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }
  
    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failcode += test_host_data_if_clause();    
    }

    // Print test summary
    if (failcode > 0) {
        printf("%d tests failed.\n", failcode);
    } else {
        printf("All tests passed.\n");
    }

    return failcode;
}