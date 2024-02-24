#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    int *data_dev = (int*)acc_malloc(sizeof(int));
    if (data_dev == NULL) {
        printf("Failed to allocate memory on the device\n");
        err = 1;
    }

    // Free the allocated memory
    acc_free(data_dev);

    // Try to free the memory again
    acc_free(data_dev);

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