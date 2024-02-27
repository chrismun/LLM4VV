#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 100
#define PRECISION 0.0001

int test_private_clause(){
    int err = 0;
    float *a, *b, *c;
    float tmp = 0.0f;
    a = (float *)malloc(n*n*n*sizeof(float));
    b = (float *)malloc(n*n*sizeof(float));
    c = (float *)malloc(n*n*sizeof(float));
    float div = 2.0f;

    // Initialize arrays
    for(int k = 0; k < n; ++k){
        for(int j = 0; j < n; ++j){
            b[k*n+j] = (float) rand() / RAND_MAX;
            c[k*n+j] = (float) rand() / RAND_MAX;
            for(int i = 0; i < n; ++i){
                a[k*n*n + j*n + i] = 0.0f;
            }
        }
    }

    #pragma acc parallel num_gangs(10)
    {
        #pragma acc loop gang
        for(int k = 0; k < n; ++k){
            #pragma acc loop worker private(tmp)
            for(int j = 0; j < n; ++j){
                // Each worker has its own private copy of tmp
                tmp = b[k*n+j] + c[k*n+j]; 
                #pragma acc loop vector
                for(int i = 0; i < n; ++i){
                    // All vector lanes within a worker use the same tmp value updated by the worker
                    a[k*n*n + j*n + i] = a[k*n*n + j*n + i] + tmp/div;
                }
            }
        }
    }

    // OPTIONAL (Can add further verification logic here)

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    srand(SEED);
    int errors = test_private_clause();
    if(errors){
        printf("Test FAILED: Errors in private clause implementation.\n");
    } else {
        printf("Test PASSED: Private clause implemented correctly.\n");
    }
    return errors;
}