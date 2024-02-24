#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_var = (int*)malloc(sizeof(int));
    *host_var = 10;

    #pragma acc data copyin(host_var)
    {
        #pragma acc host_data use_device(host_var)
        {
            if (acc_is_present(host_var, sizeof(int)) && acc_deviceptr(host_var) == host_var) {
                printf("Test passed: use_device clause is working properly.\n");
            } else {
                printf("Test failed: use_device clause is not working properly.\n");
                err = 1;
            }
        }
    }

    free(host_var);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}