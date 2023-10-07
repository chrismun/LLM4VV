#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy device, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int *h_array = (unsigned int*)malloc(100 * sizeof(unsigned int));
    unsigned int *d_array;

    /* fill h_array with some random data */
    for(int i = 0; i < 100; i++) {
        h_array[i] = rand()%100;
    }

    d_array = (unsigned int*)acc_malloc(100 * sizeof(unsigned int));
    
    /* copy array to device using acc_memcpy_to_device */
    acc_memcpy_to_device(d_array, h_array, 100*sizeof(unsigned int));

    /* copy array back from device to host */
    acc_memcpy_from_device(h_array, d_array, 100*sizeof(unsigned int));

    /* check data */
    for(int i = 0; i < 100; i++) {
        if (h_array[i] != d_array[i]) {
            err = 1;
            break;
        }
    }

    /* clean up */
    acc_free(d_array);
    free(h_array);    

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