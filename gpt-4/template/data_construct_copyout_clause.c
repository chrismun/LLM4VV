#include "acc_testsuite.h"

// Test function: data construct copyout clause
int test_copyout(){
    int err = 0;
    srand(SEED);
    float* a=(float*)malloc(N*sizeof(float));
    float* b=(float*)malloc(N*sizeof(float));

    for(int i=0; i<N; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0;
    }

    #pragma acc data copyout(b[0:N])
    {
        #pragma acc parallel loop copyin(a[0:N])
        for(int i=0; i<N; i++){
            b[i] = a[i] * 2.0f;
        }
    }

    for(int i=0; i<N; i++){
        if(b[i] != a[i]*2.0f){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = test_copyout();
    if (failed != 0){
        failcode = (1 << 0);
    }

    return failcode;
}