#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *d_a;
    int structured_ref_count = 0;
    int dynamic_ref_count = 0;

    a = (int *)malloc(sizeof(int));
    *a = 10;

    d_a = (int *)acc_malloc(sizeof(int));
    acc_memcpy(d_a, a, sizeof(int));

    // Increment structured reference counter
    structured_ref_count++;

    // Increment dynamic reference counter
    dynamic_ref_count++;

    // Check if reference counters are working properly
    if (structured_ref_count != 1 || dynamic_ref_count != 1) {
        err = 1;
    }

    // Decrement dynamic reference counter
    dynamic_ref_count--;

    // Check if reference counters are working properly
    if (structured_ref_count != 1 || dynamic_ref_count != 0) {
        err = 1;
    }

    acc_free(d_a);
    free(a);

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