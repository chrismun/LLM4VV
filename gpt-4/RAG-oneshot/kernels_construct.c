#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

/* determine the data type */
#define T float
#define PRECISION 1.e-8

/* fill array with random data */
#define INIT_DATA(X,S) do { srand(S); for(int i=0; i<N; ++i) X[i] = ((T) rand())/RAND_MAX; } while(0)

/* test for equality within some precision */
#define CHECK(X,Y) do { if (fabs(X-Y)>PRECISION) { printf("Validation failed at line %d\n", __LINE__); exit(1); } } while(0)

/* use this to run kernel on GPU */
#pragma acc routine seq
void axpy(T a, T *x, T *y, int n) {
    #pragma acc loop independent
    for(int i=0; i<n; ++i) {
        y[i] += a*x[i];
    }
}

int main() {
    const int N = 2048;
    T *x, *y, tmp;
    x = (T*)malloc(N*sizeof(T));
    y = (T*)malloc(N*sizeof(T));
    T a = 2.0;
    INIT_DATA(x,1);
    INIT_DATA(y,2);

    printf("Testing OpenACC kernels compiler implementation...\n");
    
    /* copy data to device */
    #pragma acc data copyin(x[0:N],a), copyout(y[0:N])
    {
        /* launch GPU kernels */
        #pragma acc kernels
        {
            axpy(a,x,y,N);
        }
    }
    
    /* validation */
    for(int i=0; i<N; ++i) {
        tmp = y[i] - a*x[i];
        CHECK(tmp, y[i]);
    }

    printf("OpenACC kernels implementation seems correct\n");
    free(x);
    free(y);
    
    return 0;
}