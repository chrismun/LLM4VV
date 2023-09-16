#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define N 1024
#define SEED 1234

#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);
    int *data = (int *)malloc(N * sizeof(int));

    #pragma acc enter data create(data[0:N])

    if(!acc_is_present(data, N*sizeof(int))){
        err = 1;
    }

    #pragma acc exit data delete(data[0:N])

    if(acc_is_present(data, N*sizeof(int))){
        err = 1;
    }

    free(data);
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