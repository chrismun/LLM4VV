#include "acc_testsuite.h"
#pragma acc routine seq
double update(double* a, int idx) {
    return a[idx] * idx;
}

int test1() {
    int err = 0;
    int N = 10240;
    double* A;
    A = (double*)malloc(sizeof(double) * N);
    srand(SEED);
    for(int i=0; i<N; i++) {
        A[i] = rand();
    }
    #pragma acc data copy(A[0:N])
    {
        #pragma acc parallel present(A[0:N])
        {
            #pragma acc loop independent
            {
                #pragma acc cache(A[0:N/2])
                for(int i=0; i<N; i++){
                    A[i] = update(A, i);
                }
            }
        }
    }

    for(int i=0; i<N; i++){
        if(fabs(A[i] - i * A[i]) > PRECISION) {
            err = 1;
            break;
        }
    }

    free(A);
    return err;
}