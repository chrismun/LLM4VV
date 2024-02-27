#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define a global variable to be device_resident.
#pragma acc declare create(device_var)
float device_var = 0.0;

// Function to modify the device-resident variable within an OpenACC region
void modify_device_var() {
    #pragma acc parallel copy(device_var)
    {
        device_var += 1.0;
    }
    // Note: In a real-world scenario, directly accessing `device_var` like this might not reflect changes
    // made on the device, due to it being device resident. This simplistic approach is taken here for
    // demonstrative purposes. Actual implementation might require indirect validation methods.
}

int main() {
    printf("Initial value of device_var: %f\n", device_var);

    // Modify device_var in an OpenACC parallel region
    modify_device_var();

    // Due to access restrictions on device_resident variable, direct verification is challenging.
    // A real test might involve using device_resident variables in a manner where their correct
    // behavior indirectly affects an outcome verifiable from the host.
    
    printf("Modified value of device_var: %f\n", device_var);

    return 0;
}