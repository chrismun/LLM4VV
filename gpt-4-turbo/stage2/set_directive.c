#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Test function to validate set directive behavior for device_num clause
int test1(){
    int err = 0;
    srand(SEED);

    // Initial device number (before setting a new one)
    int initial_device_num = acc_get_device_num(acc_device_not_host);

    int num_devices = acc_get_num_devices(acc_device_not_host);
    if(num_devices > 1) {
        // Attempt to set device to a different device if available
        int new_device_num = (initial_device_num + 1) % num_devices;
        #pragma acc set device_num(new_device_num)
        
        // Verify if device_num setting is effective
        int current_device_num = acc_get_device_num(acc_device_not_host);
        if(current_device_num != new_device_num) {
            printf("Failed to set device_num with OpenACC set directive.\n");
            err++;
        }

        // Revert to initial device to clean up
        #pragma acc set device_num(initial_device_num)
        if(acc_get_device_num(acc_device_not_host) != initial_device_num) {
            printf("Failed to revert device_num with OpenACC set directive.\n");
            err++;
        }
    } else {
        // If not enough devices, pass but notify
        printf("Not enough devices for testing set device_num, but this is not an error.\n");
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}