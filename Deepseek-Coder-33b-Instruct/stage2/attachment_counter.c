#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc data copyin(host_ptr[0:1])
    {
        // Attach the host pointer to the device
        #pragma acc attach(host_ptr)

        // Check if the attachment counter is 1
        if (acc_get_attachment_counter(host_ptr) != 1) {
            err = 1;
        }

        // Detach the host pointer from the device
        #pragma acc detach(host_ptr)

        // Check if the attachment counter is 0
        if (acc_get_attachment_counter(host_ptr) != 0) {
            err = 1;
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
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}