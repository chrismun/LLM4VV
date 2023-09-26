#include "acc_testsuite.h"
#ifndef T1
#define LENGTH 1024
#define VECTOR_LENGTH 256

float A[LENGTH];
float B[LENGTH];
float C[LENGTH];
float D[LENGTH];

//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int chunk_size = LENGTH / VECTOR_LENGTH;
    int err = 0;
    
    // initialize arrays with random data
    for(int i=0; i<LENGTH; i++) {
        A[i] = (float)rand()/(float)(RAND_MAX);
        B[i] = (float)rand()/(float)(RAND_MAX);
        C[i] = 0.0f;
    }
    
    // expected results on CPU
    for(int i=0; i<LENGTH; i++) {
        D[i] = A[i] + B[i];
    }

    // vector addition on GPU
    #pragma acc parallel present(A,B,C) vector_length(VECTOR_LENGTH)
    {
    #pragma acc loop vector
    for (int i=0; i<LENGTH; i++){
        C[i] = A[i] + B[i];
    }
    }

    // check the result
    for(int i=0; i<LENGTH; i++) {
        if(fabs(C[i] - D[i]) > 1e-5) {
            err = 1;
            break;
        }
    }
    
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