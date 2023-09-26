#include "acc_testsuite.h"

#ifndef T1
/*T1:data present clause,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    /* Input Vector. */
    float* h_vec = (float* )malloc (SIZE * sizeof (float));
    /* For CUDA. */
    float* d_vec;

    /* Initialize array on the host. */
    for (int i = 0; i < SIZE; i++) {
      h_vec[i] = 1.0f;
    }

    /* ALLOC on GPU and COPY from Host to GPU (CUDA) */
    #pragma acc data copyin(h_vec[0:SIZE])
    {
        /* CUDA Pointer */
        #pragma acc host_data use_device(h_vec)
        {
            d_vec = h_vec;
        }

        /* Trying to increment values on the GPU */
        #pragma acc kernels deviceptr(d_vec) present(d_vec[0:SIZE])
        {
            for (int i = 0; i < SIZE; i++) {
                d_vec[i] += 1.0f;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if(fabsf(h_vec[i] - 2.0f) > 0.0f){
            err = 1;
        }
    }

    free(h_vec);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
    #ifndef T1
        failed = 0;
        for (int x = 0; x < NUM_TEST_CALLS; ++x) {
            failed = failed + test1();
        }
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    #endif
    return failcode;
}