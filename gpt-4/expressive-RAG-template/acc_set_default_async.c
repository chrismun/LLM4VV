#include "acc_testsuite.h"

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int* vector_host = (unsigned int*)malloc(10*sizeof(unsigned int));
    unsigned int* vector_device = (unsigned int*)malloc(10*sizeof(unsigned int));
    for (int x = 0; x < 10; ++x){
        vector_host[x] = rand() / (float)RAND_MAX * 10; 
    }
    
    acc_init(acc_device_default);
    acc_set_default_async(0);
    #pragma acc enter data copyin(vector_host[0:10])
    #pragma acc parallel loop gang present(vector_host[0:10]) copyout(vector_device[0:10]) async(0)
    for (int x = 0; x < 10; ++x){
        vector_device[x] = vector_host[x];
    }

    acc_wait_all();
    #pragma acc exit data delete(vector_host[0:10])

    for (int x = 0; x < 10; ++x){
        if(vector_host[x] != vector_device[x]){
          err = 1;
        }
    }
    free(vector_host);
    free(vector_device);

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