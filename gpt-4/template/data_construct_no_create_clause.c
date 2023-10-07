#include "openacc_testsuite.h"
#ifndef T1
#define N 1024
int test1(){
    int err = 0;
    int *array_host = (int*) malloc(sizeof(int) * N);
    int *array_device = (int*) malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
        array_host[i] = rand() % 100;
    }

    #pragma acc enter data create(array_device[0:N])

    #pragma acc parallel loop copyout(array_device[0:N]) no_create(array_device[0:N])
    for (int i = 0; i < N; i++) {
        array_device[i] = array_host[i];
    }

    #pragma acc exit data delete(array_device[0:N])

    for (int i = 0; i < N; i++) {
        if(array_device[i] != array_host[i]){
            err = 1;
        }
    }

    free(array_host);
    free(array_device);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    srand(time(NULL));
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}