#include <stdlib.h>
#include <openacc.h>
#include <assert.h>

#define SIZE 1000
#define NUM_TEST_CALLS 10

// function to test the OpenACC compiler implementation
int test1(){
    int err = 0;
    float *a, *b, *c;
    a=(float *)malloc(SIZE*sizeof(float));
    b=(float *)malloc(SIZE*sizeof(float));
    c=(float *)malloc(SIZE*sizeof(float));

    // Initiate data
    for(int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc parallel loop copy(a[0:SIZE],b[0:SIZE]) async(1)
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    #pragma acc wait(1)

    for(int i = 0; i < SIZE; i++) {
        if (c[i] != i + i) {
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);
    free(c);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
            break;
        }
     }
    assert(failcode == 0);
    return failcode;
}