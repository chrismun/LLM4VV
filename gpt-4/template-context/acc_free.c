#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
/* T1:acc_free, V:2.7-3.3 */
int test1() {
    int err = 0;
    size_t num_bytes = 1024;
    void *dev_ptr = NULL;
    srand(SEED);

    /* Allocate some data on the device */
    dev_ptr = acc_malloc(num_bytes);
    if (dev_ptr == NULL) {
        printf("acc_malloc failed\n");
        return 1;
    }

    /* Free the memory */
    acc_free(dev_ptr);

    /* Try to access the memory again, should cause an error */
    #pragma acc parallel present(dev_ptr)
    {
        /* Would cause an error if the memory is actually freed */
    }
    err = acc_get_cuda_error();

    /* Check if memory was freed properly */
    if (err != 0) {
        printf("Memory was not freed properly, error: %d\n", err);
        return 1;
    }

    return 0;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}