#include "acc_testsuite.h"
#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;
    float* a = (float*)malloc(N*sizeof(float));
    float* b = (float*)malloc(N*sizeof(float));
    float* res = (float*)malloc(N*sizeof(float));
    srand(SEED);

    #pragma acc data copy(a[0:N],b[0:N],res[0:N])
    {
        for(int i=0; i<N; i++){
            a[i] = rand()/(float)RAND_MAX;
            b[i] = rand()/(float)RAND_MAX;
        }
        
        #pragma acc kernels
        for(int i=0; i<N; i++){
            res[i] = a[i] + b[i];
        }
        #pragma acc shutdown

        for(int i=0; i<N; i++){
            res[i] = a[i] - b[i];
        }
    }

    for(int i=0; i<N; i++){
        if(fabs(res[i] - (a[i] - b[i])) > PRECISION){
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);
    free(res);

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