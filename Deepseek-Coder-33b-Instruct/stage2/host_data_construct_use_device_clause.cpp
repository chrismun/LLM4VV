#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc data copyin(host_ptr)
    {
        #pragma acc host_data use_device(host_ptr)
        {
            if (acc_is_present(host_ptr, sizeof(int))) {
                if (acc_deviceptr(host_ptr) != (void*)host_ptr) {
                    err = 1;
                }
            }
        }
    }

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