#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define T1
#define NUM_TEST_CALLS 10
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc data copyin(host_ptr)
    {
        // Attach the host pointer to the device memory
        #pragma acc attach(host_ptr)

        // Check if the host pointer is attached to the device memory
        if (acc_is_present(host_ptr, sizeof(int)) == 0) {
            err = 1;
            printf("Error: host_ptr is not attached to the device memory\n");
        }

        // Detach the host pointer from the device memory
        #pragma acc detach(host_ptr)

        // Check if the host pointer is detached from the device memory
        if (acc_is_present(host_ptr, sizeof(int)) != 0) {
            err = 1;
            printf("Error: host_ptr is not detached from the device memory\n");
        }
    }

    free(host_ptr);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}