#include "acc_testsuite.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifndef T1
/*T1:acc memcpy d2d,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(time(NULL));

    const size_t N = 1000;
    int dev_num_dest = 0;  // Device number for destination
    int dev_num_src = 1;   // Device number for source

    // Allocate and prepare source data
    float *data_arg_src = (float*) malloc(N * sizeof(float));
    for(size_t i = 0; i < N; ++i){
        data_arg_src[i] = rand() / (float)RAND_MAX;
    }

    // Allocate host memory for destination data
    float* data_arg_dest = (float*) malloc(N * sizeof(float));

    // Copy between devices
    acc_memcpy_d2d((void*)data_arg_dest, (void*)data_arg_src, N * sizeof(float), dev_num_dest, dev_num_src);

    // Check if copying was successful
    for(size_t i = 0; i < N; ++i){
        if(data_arg_dest[i] != data_arg_src[i]){
            err = 1;
            break;
        }
    }

    free(data_arg_src);
    free(data_arg_dest);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}