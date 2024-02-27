#include <stdlib.h>
#include <stdio.h>

#ifndef T1
// Test for OpenACC routine directive
int test1(){
    int err = 0;
    const int a = 3, b = 5; // Inputs for our simple test
    int result_host = 0;
    int result_device = 0;

    // Define a simple addition function with OpenACC routine directive for seq execution
    #pragma acc routine seq
    int add_numbers(int x, int y){
        return x + y;
    }

    // Perform addition on the host
    result_host = add_numbers(a, b);

    // Perform addition on the device
    #pragma acc parallel copyout(result_device)
    {
        result_device = add_numbers(a, b);
    }

    // Check if the results match
    if (result_host != result_device){
        printf("Test failed: host result %d does not match device result %d\n", result_host, result_device);
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    // Report test results and exit
    if(failcode == 0){
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed with code %d.\n", failcode);
    }

    return failcode;
}