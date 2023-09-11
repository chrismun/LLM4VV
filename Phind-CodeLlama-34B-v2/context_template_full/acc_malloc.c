#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc malloc,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    size_t bytes = rand() % 10000 + 1;
    void *host_ptr = malloc(bytes);
    void *device_ptr = acc_malloc(bytes);

    if (device_ptr == NULL){
        fprintf(stderr, "acc_malloc returned NULL pointer\n");
        err = 1;
    }

    acc_free(device_ptr);
    free(host_ptr);

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