#include "acc_testsuite.h"

#ifndef T1
/*T1:acc update device,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    float * random_array = (float*) malloc(10 * sizeof(float));
    for(int i = 0; i < 10; i++) {
        random_array[i] = rand();
    }

    #pragma acc enter data copyin(random_array[0:10])

    float * gpu_array;
    gpu_array = (float*)acc_copyin((const void*)random_array, 10 * sizeof(float));
    
    for(int i = 0; i < 10; i++) {
        random_array[i] = 0.0;
    }

    acc_update_device((h_void*)random_array, 10 * sizeof(float));

    for(int i = 0; i < 10; i++) {
        if(gpu_array[i] != random_array[i]) {
            err = 1;
            break;
        }
    }

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