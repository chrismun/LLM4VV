#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc data copyin(host_ptr[0:1])
    {
        #pragma acc attach(host_ptr)
        {
            if(host_ptr[0] != 10){
                err = 1;
            }
        }

        #pragma acc detach(host_ptr)
        {
            if(host_ptr[0] != 10){
                err = 1;
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