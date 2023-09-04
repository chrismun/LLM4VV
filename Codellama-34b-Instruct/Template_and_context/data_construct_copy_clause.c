#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    acc_shared_region_t region = acc_create_shared_region(sizeof(int), 1);
    if (region == NULL) {
        err = 1;
        return err;
    }

    // Create a pointer to the shared memory region
    int* shared_ptr = (int*)acc_get_shared_region_ptr(region);
    if (shared_ptr == NULL) {
        err = 1;
        return err;
    }

    // Initialize the shared memory region with a random value
    *shared_ptr = rand();

    // Create a copy of the shared memory region
    acc_shared_region_t copy = acc_create_shared_region(sizeof(int), 1);
    if (copy == NULL) {
        err = 1;
        return err;
    }

    // Copy the shared memory region to the copy
    acc_copy_shared_region(region, copy);

    // Check that the copy has the same value as the original
    if (*(int*)acc_get_shared_region_ptr(copy) != *shared_ptr) {
        err = 1;
        return err;
    }

    // Free the copy
    acc_free_shared_region(copy);

    // Free the original
    acc_free_shared_region(region);

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