#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_data = (int*)malloc(sizeof(int));
    *host_data = 1;

    #pragma acc data copyin(host_data)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < 100; i++) {
                *host_data += 1;
            }
        }
    }

    if (*host_data != 101) {
        err = 1;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}