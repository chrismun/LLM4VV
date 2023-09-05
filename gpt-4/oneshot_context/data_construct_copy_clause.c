#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    const int N = 1000000;
    double *a = (double*)malloc(N*sizeof(double));
    double *b = (double*)malloc(N*sizeof(double));

    for(int i=0; i<N; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copy(a[0:N], b[0:N])    /*copy clause*/
    {        
        #pragma acc parallel loop
        for(int i=0; i<N; i++){
            b[i] = a[i];
        }
    }

    /* printing first and last element for check */
    printf("%f   %f\n", b[0], b[N-1]);

    return 0;
}