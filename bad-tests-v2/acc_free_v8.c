#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc free,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *data_dev;
    int data_size = 1024;
    data_dev = (int *)acc_malloc(data_size * sizeof(int));

    if(data_dev == NULL){
        printf("acc_malloc failed to allocate memory on the device\n");
        return 1;
    }

    acc_free(data_dev);

    if(acc_get_device_type() == acc_device_host){
        if(data_dev != NULL){
            printf("acc_free failed to free memory on the host\n");
            err = 1;
        }
    } else {
        if(data_dev != NULL){
            printf("acc_free failed to set pointer to NULL after freeing memory on the device\n");
            err = 1;
        }
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