#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:serial construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* host_array = (int*)malloc(10*sizeof(int));
    int* device_array;

    // Initialize the host array
    for(int i=0; i<10; i++) {
        host_array[i] = i;
    }

    #pragma acc enter data copyin(host_array[0:10])
    #pragma acc serial present(host_array[0:10]) self
    {
        device_array = acc_copyin(host_array, 10*sizeof(int));

        if(device_array == NULL) {
            err = 1;  // Expect the array to be present on the local device
        }

        #pragma acc exit data delete(host_array[0:10])
        free(host_array);  // Clean up
    }
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