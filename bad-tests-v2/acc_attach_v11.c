#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float* host_data = (float*)malloc(sizeof(float) * SIZE);
    float** dev_ptr = (float**)acc_malloc(sizeof(float*));

    for(int i=0; i<SIZE; i++)
        host_data[i] = rand()/(float)RAND_MAX;

    *dev_ptr = (float*)acc_copyin(host_data, sizeof(float) * SIZE);

    acc_attach((void**)dev_ptr);
    acc_memcpy_to_device(host_data, *dev_ptr, sizeof(float) * SIZE);

    acc_detach((void**)dev_ptr);
    if (*dev_ptr != NULL) {
        err = 1;
    }

    free(host_data);
    acc_free(dev_ptr);

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
    if (failed > 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}