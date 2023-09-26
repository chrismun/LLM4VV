#include "acc_testsuite.h"
#include <openacc.h>

int test_acc_free(){
    int err = 0;

    size_t size = 100;
    void *dev_ptr;

    #pragma acc data create(size)
    {
        dev_ptr = acc_malloc(size*sizeof(size_t));
    }

    acc_free(dev_ptr);
    
    #pragma acc data present(size)
    {
        size_t* check_ptr = (size_t *) dev_ptr;
        if (check_ptr != NULL){
           err = 1;
        }
    }
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_free();
    }

    if (failed != 0){
        failcode = failcode + 1;
    }

    return failcode;
}