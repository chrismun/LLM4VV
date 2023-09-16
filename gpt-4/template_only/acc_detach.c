#include "acc_testsuite.h"
#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float* vec1, *vec2;
    float sum = 0.0;
    int size = 10000;

    vec1 = (float*) malloc(sizeof(float) * size);
    vec2 = (float*) malloc(sizeof(float) * size);

    for(int i=0; i<size; i++) {
        vec1[i] = rand() % 100;
        vec2[i] = rand() % 100;
    }

    acc_copyin(vec1, size*sizeof(float));
    acc_copyin(vec2, size*sizeof(float));
    acc_detach(vec1, vec2, size);

    #pragma acc kernels present(vec1[0:size], vec2[0:size])
    {
        for(int i=0; i<size; i++)
            sum += vec1[i] * vec2[i];
    }

    if(sum != expected_sum){
        err = 1;
    }

    free(vec1);
    free(vec2);
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