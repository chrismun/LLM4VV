#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main(){
    int i;
    double *a, *b;

    a = (double*)malloc(N*sizeof(double));
    b = (double*)malloc(N*sizeof(double));

    for(i=0; i<N; i++){
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc kernels
    {
        #pragma acc loop
        for(i=0; i<N; i++){
            b[i] = a[i];
        }
    }

    #pragma acc exit data copyout(b[0:N])

    for(i=0; i<N; i++){
        if(a[i] != b[i]){
            printf("Test failed at index %d: %f != %f\n", i, a[i], b[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}