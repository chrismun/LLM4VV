#include "acc_testsuite.h"
#include "stdlib.h"

#ifndef T1
/*T1:host_data construct if_present clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    float* hostarr;
    float* devptr;
    int size = 512;
    int dev = acc_device_nvidia; //assuming Nvidia device
    acc_set_device_type(dev);
    hostarr = (float*) malloc (size * sizeof(float));

    acc_init(dev);
    devptr = (float*) acc_malloc(size * sizeof(float));

    #pragma acc enter data copyin(hostarr[0:size])

        #pragma acc host_data use_device(devptr) if_present
        {
            if ( ! acc_is_present(devptr, size * sizeof(float))){
                err = 1;
            }
        }
        
    #pragma acc exit data delete(hostarr[0:size])

    acc_free(devptr);
    free(hostarr);
    acc_shutdown(dev);
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