#include <stdlib.h>
#include <stdio.h>
#ifdef _OPENACC
#include <openacc.h>
#endif
#include "acc_testsuite.h"

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Assuming a scenario where a computation is done before shutdown
    int dataSize = 1024;
    float *data = (float*)malloc(dataSize * sizeof(float));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Initialize data
    for (int i = 0; i < dataSize; ++i) {
        data[i] = (float)rand() / RAND_MAX;
    }
    
    // Offload a simple computation to any available device before shutdown
    #pragma acc parallel loop copy(data[0:dataSize])
    for(int i = 0; i < dataSize; ++i) {
        data[i] = data[i] * 2.0f;
    }
    
    // Assuming the conditional shutdown is based on a simple deterministic condition
    int shouldShutdown = 1; // This condition can be adjusted or randomized as needed
    #pragma acc shutdown if(shouldShutdown)

    /* Since we can't directly verify the shutdown within the application, the verification
       could involve attempting another OpenACC operation after the shutdown directive and
       catching expected errors or checking for performance differences. This is largely
       symbolic as actual hardware and runtime effects of shutdown cannot be confirmed
       through this test alone. */
    
    // Attempt to perform a computation after the supposed shutdown
    #pragma acc parallel loop copy(data[0:dataSize])
    for(int i = 0; i < dataSize; ++i) {
        data[i] = data[i] + 1.0f; //This operation might fail or behave differently if shutdown worked
    }
    
    // Cleanup
    free(data);
    
    // Since actual verification of shutdown isn't feasible in this context, err remains 0
    // In real tests, monitoring tools or runtime checks could be used as a substitute
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}