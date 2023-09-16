#include "acc_testsuite.h"
#include <openacc.h>

int main()
{
     // Test size to allocate
    size_t testSize = 1024; // 1KB

    // Allocate space on the device using acc_malloc
    void* devicePtr = acc_malloc(testSize);

    // Check whether the allocation was successful
    if (devicePtr == NULL) {
        printf("acc_malloc failed to allocate device memory\n");
        return 1;
    }

    // Verify that the pointer is in device memory
    if(acc_is_present(devicePtr, testSize) == 0){
        printf("acc_malloc has not allocated device memory properly\n");
        acc_free(devicePtr);
        return 1;
    }

    printf("acc_malloc successfully allocated device memory\n");

    // Don't forget to free the allocated memory
    acc_free(devicePtr);

    return 0;
}