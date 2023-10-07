#include <openacc.h>

int main() {
    // Initialize the runtime for the GPU device type
    #pragma acc init device_type(gpu)

    // Perform some computation on the GPU
    #pragma acc parallel num_gangs(10)
    {
        // ...
    }

    // Shut down the runtime
    #pragma acc shutdown

    return 0;
}