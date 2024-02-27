#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 10;
    int *hostArray = (int*)malloc(size * sizeof(int));
    
    // Initializing host array
    for(int i = 0; i < size; ++i) {
        hostArray[i] = rand() % 100;
    }

    // Manually ensuring the data is present on the device
    #pragma acc enter data copyin(hostArray[0:size])
    
    // Obtaining device pointer
    void* devicePtr = acc_deviceptr(hostArray);
    
    if(devicePtr == NULL) {
      printf("Device pointer is null\n");
      err++;
    } else {
      printf("Device pointer obtained\n");
    }

    // Checking if the device pointer is not the same as host pointer (since the data is on the device)
    if(devicePtr == (void*)hostArray) {
      printf("Device pointer should not be equal to host pointer\n");
      err++;
    }

    #pragma acc exit data delete(hostArray[0:size])
  
    free(hostArray);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}