#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1000
#define PRECISION 1e-5

#ifndef T2
// T2:host_data,if_present,V:1.0-3.1
int test2() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *device_a_ptr = NULL;

    // Initialize array 'a'
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (float)(RAND_MAX / 10);
    }

    // Allocate and copy data to device, but use device_a_ptr to track device memory
    #pragma acc enter data copyin(a[0:n])
    device_a_ptr = acc_deviceptr(a);

    // Modify 'a' on the device if present; should be present at this point
    #pragma acc parallel present(device_a_ptr[0:n]) if_present
    for (int x = 0; x < n; ++x) {
        device_a_ptr[x] = device_a_ptr[x] + 1.0f;
    }
    
    // Exit data from device
    #pragma acc exit data copyout(a[0:n])

    // Validate that values in 'a' have been incremented
    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - (x / (float)(RAND_MAX / 10) + 1.0f)) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < 1; ++x) {  // Run the test once, but loop structure is kept for consistency
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif
    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL: %d\n", failcode);
    }
    return failcode;
}