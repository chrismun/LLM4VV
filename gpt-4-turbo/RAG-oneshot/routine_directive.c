#include <stdio.h>
#include <openacc.h>
#include <math.h>

#pragma acc routine seq
void sequential_function(int *data) {
    *data += 1;
}

#pragma acc routine seq nohost
void device_only_function(int *data) {
    *data += 10;
}

int main() {
    int host_data = 0;
    int device_data = 0;
    
    // Execute on the host
    sequential_function(&host_data);
    
    // Attempt to execute on the device (if nohost clause is ignored, this will fail to compile or execute)
    #pragma acc parallel copy(device_data)
    {
        device_only_function(&device_data);
    }
    
    printf("Host Data: %d\n", host_data); // Expecting 1
    printf("Device Data: %d\n", device_data); // Expecting 10 (only if device_only_function compiles for the device)
    
    return 0;
}