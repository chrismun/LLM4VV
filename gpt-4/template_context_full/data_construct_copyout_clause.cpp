#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct copyout clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int array_size = 100;
    float* a = (float*)malloc(sizeof(float) * array_size);
    float* result_array = (float*)malloc(sizeof(float) * array_size);
    
    // Initializing the arrays with random numbers
    for (int i = 0; i < array_size; ++i) {
        a[i] = ((float)rand()/(float)(RAND_MAX)) * 10.0;
    }

    // Calculate square of each element using OpenACC
#pragma acc parallel loop copyout(result_array[0:100])
    for (int i = 0; i < array_size; i++) {
        result_array[i] = a[i] * a[i];
    }

    // Validation
    for (int i = 0; i < array_size; i++) {
        float expected_value = a[i] * a[i];
        if (fabs(result_array[i] - expected_value) > PRECISION) {
            err = 1;
            break;
        }
    }

    free(a);
    free(result_array);

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