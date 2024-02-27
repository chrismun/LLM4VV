#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 12345
#define n 1000
#define PRECISION 0.0001

#ifndef T1
// T1:kernels,loop,V:1.0-3.1
int test_seq_clause(){
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    // Initializing arrays with dummy values
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (float)(RAND_MAX / 10);
        b[x] = -1; // default value to indicate unprocessed
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels
        {
            // Using seq clause to enforce sequential execution
            #pragma acc loop seq
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Verification
    for (int x = 0; x < n; ++x){
        if (abs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = test_seq_clause();
    if (failed != 0){
        failcode = 1;
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}