#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SIZE 100
#define SEED 12345
#define NUM_TEST_CALLS 10

int acc_update_self_test() {
    int i;
    int err = 0;
    int host_data[SIZE];
    int device_data[SIZE];

    /* Initialize data on the host */
    srand(SEED);
    for(i = 0; i < SIZE; i++) {
        host_data[i] = rand() % SIZE;
    }

    /* Copy data to the device */
    #pragma acc enter data copyin(host_data)

    /* Update data on the device */
    #pragma acc parallel loop present(host_data)
    for(i = 0; i < SIZE; i++) {
        host_data[i] += i;
    }

    /* Copy data back to the host */
    #pragma acc update self(host_data)

    /* Verify the results */
    for(i = 0; i < SIZE; i++) {
        if(host_data[i] != (i + (rand() % SIZE))) {
            err += 1;
        }
    }

    /* Cleanup accelerator device */
    #pragma acc exit data delete(host_data)

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + acc_update_self_test();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("OpenACC acc_update_self test PASSED\n");
    } else {
        printf("OpenACC acc_update_self test FAILED\n");
    }

    return failcode;
}