#include <stdlib.h>
#include <openacc.h>

#define T1
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int *data_dev = NULL;

    // Allocate memory on the device
    data_dev = (int*)acc_malloc(sizeof(int));
    if (data_dev == NULL) {
        err = 1;
        return err;
    }

    // Free the allocated memory
    acc_free(data_dev);

    // Check if the memory is freed
    if (acc_is_present(data_dev, sizeof(int))) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
#ifdef T1
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