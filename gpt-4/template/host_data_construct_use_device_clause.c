#include "acc_testsuite.h"
#ifndef T1
//#T1:host_data construct use_device clause, Version: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    float* a_host;
    float* a_device;
    a_host = (float*)malloc(N * sizeof(float));
    a_device = (float*)acc_malloc(N * sizeof(float));

    for(int i = 0; i < N; i++){
        a_host[i] = (float)rand() / (float)(RAND_MAX / 2.0) - 1.0; // -1.0 to 1.0
    }

    #pragma acc enter data copyin(a_host[0:N]) create(a_device[0:N])
    for(int i = 0; i < N; i++){
        #pragma acc host_data use_device(a_device)
        {
            a_device[i] = a_host[i];
        }
    }

    for(int i = 0; i < N; i++){
        if (fabs(a_device[i] - a_host[i]) > PRECISION){
            err = 1;
        }
    }

    #pragma acc exit data delete(a_host[0:N], a_device[0:N])
    free(a_host);
    acc_free(a_device);

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