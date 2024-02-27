#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,loop,construct-independent,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    const int vector_size = 1024;
    real_t *a = (real_t *)malloc(vector_size * sizeof(real_t));
    real_t *b = (real_t *)malloc(vector_size * sizeof(real_t));

    // Initialize arrays with random values
    for (int i = 0; i < vector_size; ++i){
        a[i] = (real_t)(rand()) / RAND_MAX;
        b[i] = 0.0;
    }

    // Using device_type clause with loop construct
    #pragma acc parallel device_type(nvidia) copyin(a[0:vector_size]) copyout(b[0:vector_size])
    {
        #pragma acc loop
        for (int i = 0; i < vector_size; ++i) {
            b[i] = a[i] * 2.0;
        }
    }

    // Verification
    for (int i = 0; i < vector_size; ++i) {
        if (fabs(b[i] - (a[i] * 2.0)) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}