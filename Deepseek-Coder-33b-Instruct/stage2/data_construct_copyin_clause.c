#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    int host_var = 10;
    int device_var = 0;

    #pragma acc data copyin(host_var)
    {
        #pragma acc kernels
        {
            device_var = host_var;
        }
    }

    if (device_var != host_var) {
        err = 1;
    }

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