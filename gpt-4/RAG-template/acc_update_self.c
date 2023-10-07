#include "acc_testsuite.h"
#ifndef T1
//T1:acc update self, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    float* a = (float*)malloc(N * sizeof(float));
    float* b = (float*)malloc(N * sizeof(float));
    float* c = (float*)malloc(N * sizeof(float));
    
    for(int i = 0; i < N; ++i){
        a[i] = (float) rand() / (float) (RAND_MAX / 100);
        b[i] = (float) rand() / (float) (RAND_MAX / 100);
    }

    #pragma acc parallel copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }

    #pragma acc update self(c[0:N])

    for(int i = 0; i < N; i++){
        if(c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);
    free(c);

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