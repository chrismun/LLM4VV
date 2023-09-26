#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int N = 1000;
    float *x = (float*)malloc(N*sizeof(float));
    float *y = (float*)malloc(N*sizeof(float));
    float *z = (float*)malloc(N*sizeof(float));

    // initialization
    for(int i = 0; i < N; i++){
        x[i] = i+1;
        y[i] = 2*(i+1);
    }

    // using data construct
    #pragma acc data copyin(x[0:N], y[0:N]) copyout(z[0:N])
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; i++){
            z[i] = x[i] + y[i];
        }
    }

    // checking results
    for(int i = 0; i < N; i++){
        if(z[i] != 3*(i+1)){
            printf("Test failed at index %d, Expected %f but got %f\n", i, 3*(i+1), z[i]);
            exit(1);
        }
    }

    printf("Test passed! \n");

    // clean up
    free(x); free(y); free(z);

    return 0;
}