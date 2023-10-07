#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define N 1024

int main(){
    int i;
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc data create(a[0:N], b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++){
                b[i] = a[i];
            }
        }
    }

    for(i = 0; i < N; i++){
        if(fabs(b[i] - a[i]) > PRECISION){
            fprintf(stderr, "Validation failed at index %d\n", i);
            return 1;
        }
    }

    printf("Validation passed\n");
    return 0;
}