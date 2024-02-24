#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#define acc_malloc(bytes) acc_malloc(bytes)

int test1(){
    int err = 0;
    srand(SEED);

    size_t bytes = rand() % 1000 + 1;
    void *ptr = acc_malloc(bytes);

    if (ptr == NULL) {
        fprintf(stderr, "acc_malloc failed to allocate %zu bytes\n", bytes);
        err = 1;
    } else {
        acc_free(ptr);
    }

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