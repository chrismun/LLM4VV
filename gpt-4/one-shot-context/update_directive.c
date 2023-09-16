#include <stdio.h>
#include <openacc.h>

#define ARR_SIZE 100

void update_acc_test() {
    int i;
    int host_arr[ARR_SIZE];
    int device_arr[ARR_SIZE];

    // Initialize host array
    for (i = 0; i < ARR_SIZE; ++i) {
        host_arr[i] = i;
    }

    // Update device array from host
    #pragma acc data copyin(host_arr) copy(device_arr)
    {
        #pragma acc update device(host_arr)
        #pragma acc parallel loop 
        for (i = 0; i < ARR_SIZE; ++i) {
            device_arr[i] = host_arr[i] * 2;
        }     

        // Update host array from device
        #pragma acc update host(device_arr)
    }

    // Print device_arr values
    for (i = 0; i < ARR_SIZE; ++i) {
        printf("%d ", device_arr[i]);
    }
}

int main() {
    update_acc_test();
    
    return 0;
}