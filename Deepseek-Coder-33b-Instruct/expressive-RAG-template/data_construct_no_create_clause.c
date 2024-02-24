#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_array = (int*)malloc(10 * sizeof(int));
    int *device_array = NULL;

    #pragma acc data copyin(host_array[0:10])
    {
        #pragma acc no_create(device_array)
        {
            device_array = (int*)acc_malloc(10 * sizeof(int));
        }
    }

    if (device_array != NULL) {
        err = 1;
    }

    free(host_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}