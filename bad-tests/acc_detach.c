#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:acc detach,V:2.0-2.7*/
int test1(){
    int err = 0;
    int *hostptr, *devptr;
    srand(SEED);

    hostptr = (int *) malloc (sizeof(int));
    *hostptr = rand();

    #pragma acc data create(devptr[0:1])
    {
        devptr = acc_copyin (hostptr, sizeof(int));
        acc_attach ((void **)&devptr);
        #pragma acc parallel present(devptr)
        {
            if (*devptr != *hostptr) err = 1;
        }
        acc_detach ((void **)&devptr);
    }

    free (hostptr);

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