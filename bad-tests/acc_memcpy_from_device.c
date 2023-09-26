#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy from device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int size = 8192;
    int h_vector[size];
    for (int i = 0; i < size; i++) h_vector[i] = i;

    void* dev_mem = acc_malloc(size * sizeof(int));
    acc_memcpy_to_device(dev_mem, h_vector, size * sizeof(int));

    #pragma acc parallel loop present(dev_mem)
        for (int i = 0; i < size; i++) {
        	int *d_vector = (int *) dev_mem;
        	d_vector[i] *= 2;
        }
    
    acc_memcpy_from_device(h_vector, dev_mem, size * sizeof(int));
    acc_free(dev_mem);
    
    for (int i = 0; i < size; i++) {
        if (h_vector[i] != i * 2) {
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