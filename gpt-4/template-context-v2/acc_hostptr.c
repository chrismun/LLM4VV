#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
    //T1:acc hostptr,V:2.7-3.3
    int test1(){
        int err = 0;
        srand(SEED);
        int array_size = 100;
        int* pointer_host = malloc(array_size * sizeof(int));
        int* pointer_device = acc_copyin(pointer_host, array_size * sizeof(int));

        for(int i = 0; i < array_size; i++)
            pointer_host[i] = i*2;

        int* found_device_pointer = acc_deviceptr(pointer_host);

        if(found_device_pointer == NULL){
            printf("Error: NULL pointer returned by acc_deviceptr\n");
            err = 1;
        }
        else if(found_device_pointer != pointer_device)
        {
            printf("Error: Mismatch between device pointers.\n");
            printf("Expected %p but got %p.\n", pointer_device, found_device_pointer);
            err = 1;
        }
        
        acc_delete(pointer_host, array_size * sizeof(int));
        free(pointer_host);

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