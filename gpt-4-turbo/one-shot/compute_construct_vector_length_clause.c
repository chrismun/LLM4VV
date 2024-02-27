#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 1024
#define SEED 123
#define PRECISION 0.00001

// Function to test vector_length clause
int test_vector_length(){
    int err = 0;
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Use the vector_length clause
    #pragma acc parallel loop vector_length(32) copyin(a[0:n]) copyout(b[0:n])
    for (int i = 0; i < n; ++i){
        b[i] = a[i];
    }

    // Verification step
    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - a[i]) > PRECISION){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    srand(SEED);
    
    int errors = test_vector_length();
    if(errors > 0){
        printf("Test failed with %d errors.\n", errors);
        return 1;
    } else {
        printf("Test passed.\n");
        return 0;
    }
}