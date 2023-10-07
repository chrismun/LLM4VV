#include "acc_testsuite.h"
#ifndef T1
/*T1:variable implicit data attributes,V:2.0-2.7*/
#define N 1000 // Size of array

int test1(){
    int err = 0;
    srand(SEED);
    float* a = (float*)malloc(sizeof(float)*N);
    float* b = (float*)malloc(sizeof(float)*N);
    float* c = (float*)malloc(sizeof(float)*N);

    // Initialize arrays
    for(int i=0; i<N; i++) {
        a[i] = (float)i;
        b[i] = (float)(N - i);
    }
    
    // Multiplication in parallel
    #pragma acc parallel loop copy(a[0:N], b[0:N], c[0:N])
    for(int i=0; i<N; i++) {
        c[i] = a[i] * b[i];
    } 

    // Check result
    for(int i=0; i<N; i++){
        if(c[i] != a[i] * b[i]) {
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