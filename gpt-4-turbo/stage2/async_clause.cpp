#include <iostream>
#include <stdlib.h>
#include <vector>
#include <openacc.h>

#ifndef T1
//T1:async clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand((unsigned int)time(NULL));

    const int dataSize = 1024;
    std::vector<int> hostData(dataSize, 1); // initialize all elements to 1
    int* deviceData;

    // Allocate memory on the device
    #pragma acc enter data copyin(hostData[0:dataSize]) create(deviceData[0:dataSize])

    // Perform operations asynchronously in two separate queues
    #pragma acc parallel loop async(1) copyout(deviceData[0:dataSize/2])
    for (int i = 0; i < dataSize / 2; ++i) {
        deviceData[i] = hostData[i] + 1;
    }

    #pragma acc parallel loop async(2) copyout(deviceData[dataSize/2:dataSize/2])
    for (int i = dataSize / 2; i < dataSize; ++i) {
        deviceData[i] = hostData[i] + 1;
    }

    // Wait for both operations to finish
    #pragma acc wait(1)
    #pragma acc wait(2)

    // Copy data back to host and check for errors
    #pragma acc exit data copyout(hostData[0:dataSize]) delete(deviceData[0:dataSize])

    for (int i = 0; i < dataSize; ++i) {
        if (hostData[i] != 2) {
            err++;
        }
    }

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
    std::cout << "Test " << (failcode ? "FAILED" : "PASSED") << std::endl;
    return failcode;
}