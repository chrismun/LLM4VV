#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a pointer to a data structure
    struct data_t *ptr = (struct data_t *)malloc(sizeof(struct data_t));
    if (ptr == NULL) {
        err = 1;
    }

    // Initialize the data structure
    ptr->a = 1;
    ptr->b = 2;
    ptr->c = 3;

    // Create a second pointer to the same data structure
    struct data_t *ptr2 = (struct data_t *)malloc(sizeof(struct data_t));
    if (ptr2 == NULL) {
        err = 1;
    }

    // Copy the data structure to the second pointer
    memcpy(ptr2, ptr, sizeof(struct data_t));

    // Verify that the data structures are equal
    if (memcmp(ptr, ptr2, sizeof(struct data_t)) != 0) {
        err = 1;
    }

    // Free the memory for the data structures
    free(ptr);
    free(ptr2);

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