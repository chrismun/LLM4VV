#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(sizeof(int));
    *host_data = 10;

    #pragma acc data create(host_data[0:1])
    {
        host_data[0] = 20;
    }

    if (*host_data != 20) {
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