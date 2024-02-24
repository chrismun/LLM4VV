#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_data = (int*) malloc(sizeof(int));
    *host_data = 1;

    #pragma acc data copyin(host_data)
    {
        #pragma acc host_data use_device(host_data) if_present
        {
            if (*host_data != 1) {
                err = 1;
            }
        }
    }

    free(host_data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}