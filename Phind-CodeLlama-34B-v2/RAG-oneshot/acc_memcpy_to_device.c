#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.0001

int main(){
    int i;
    float *a, *b;

    a = (float *)malloc(N * sizeof(float));
    b = (float *)malloc(N * sizeof(float));

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc kernels
    {
        #pragma acc loop
        for(i = 0; i < N; i++){
            b[i] = a[i];
        }
    }

    #pragma acc exit data copyout(b[0:N])

    for(i = 0; i < N; i++){
        if(fabs(b[i] - a[i]) > PRECISION){
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}