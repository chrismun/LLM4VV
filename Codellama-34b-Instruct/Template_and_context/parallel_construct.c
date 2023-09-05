#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) device_type(acc_device_default)
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            printf("Gang %d, Worker %d, Vector %d: %d\n", acc_get_gang_id(), acc_get_worker_id(), acc_get_vector_id(), i);
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) device_type(acc_device_default)
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            printf("Gang %d, Worker %d, Vector %d: %d\n", acc_get_gang_id(), acc_get_worker_id(), acc_get_vector_id(), i);
        }
    }

    return failcode;
}