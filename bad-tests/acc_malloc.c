#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:acc malloc,V:2.0-2.7*/
int test1(){
    int err = 0;
    size_t size = 1024;
    unsigned seed = 123456;

    void *d_pointer = acc_malloc(size);
    
    /* acc_malloc should return a null pointer if the allocation failed or size is zero */
    if(d_pointer == NULL){
        err = 1;
    }
    else{
        /* Try using the allocated device memory */
        #pragma acc parallel deviceptr(d_pointer)
        {
            ((double*)d_pointer)[0] = (double)rand_r(&seed);
        }

        /* Then free it */
        acc_free(d_pointer);
    }
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