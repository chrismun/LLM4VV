#include "acc_testsuite.h"
#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int length = 10000;
    float * a = (float*)malloc(length * sizeof(float));
    float * b = (float*)malloc(length * sizeof(float));
    float * c = (float*)malloc(length * sizeof(float));

    float * d_a;
    int error = 0;
    cudaMalloc((void**)&d_a, length * sizeof(float));
    
    #pragma acc data deviceptr(d_a)
    {
       for(int i=0; i<length; i++) {
           #pragma acc kernels
           d_a[i] = a[i] + b[i];
           // Check results
           if(fabs(d_a[i] - (a[i] + b[i])) > 1.0e-5) {
               err = 1;
           }
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