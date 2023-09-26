#include "acc_testsuite.h"
#ifndef T1
/*T1:attachment counter,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *d_a = (int *)acc_malloc(10 * sizeof(int));

    // Attach pointer to device memory
    acc_attach(a, d_a, 10 * sizeof(int));

    // Check attachment counter
    if (acc_get_attach_counter(a) != 1) {
        err = 1;
    }

    // Increment attachment counter
    acc_attach(a, d_a, 10 * sizeof(int));

    // Check attachment counter
    if (acc_get_attach_counter(a) != 2) {
        err = 1;
    }

    // Decrement attachment counter
    acc_detach(a);

    // Check attachment counter
    if (acc_get_attach_counter(a) != 1) {
        err = 1;
    }

    // Decrement attachment counter to zero
    acc_detach(a);

    // Check attachment counter
    if (acc_get_attach_counter(a) != 0) {
        err = 1;
    }

    // Check if pointer is detached
    if (acc_is_present(a, 10 * sizeof(int)) != 0) {
        err = 1;
    }

    free(a);
    acc_free(d_a);

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