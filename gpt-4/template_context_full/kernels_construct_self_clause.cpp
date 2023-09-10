#include "acc_testsuite.h"
#ifndef T1
/*T1: kernels construct self clause, V:2.0-2.7 */

int test1(){
    int err = 0;
    srand(SEED);
    int *a_host = (int*)malloc(1000*sizeof(int));
    int *b_host = (int*)malloc(1000*sizeof(int));
    int *c_host = (int*)malloc(1000*sizeof(int));
    int *a_device = (int*)acc_malloc(1000*sizeof(int));
    int *b_device = (int*)acc_malloc(1000*sizeof(int));
    int *c_device = (int*)acc_malloc(1000*sizeof(int));

    for(int i = 0; i < 1000; i++){
        a_host[i] = rand() % 100;
        b_host[i] = rand() % 100;
    }

    acc_memcpy_to_device(a_host, a_device, 1000*sizeof(int));
    acc_memcpy_to_device(b_host, b_device, 1000*sizeof(int));

    #pragma acc kernels present(a_device[0:1000], b_device[0:1000], c_device[0:1000]) if(acc_on_device(acc_device_not_host))
    {
        for(int i = 0; i < 1000; i++){
            c_device[i] = a_device[i] + b_device[i];
        }
    }

    acc_memcpy_to_host(c_device, c_host, 1000*sizeof(int));

    for(int i = 0; i < 1000; i++){
        if(c_host[i] != a_host[i] + b_host[i]){
            err = 1;
        }
    }

    acc_free(a_device);
    acc_free(b_device);
    acc_free(c_device);
    free(a_host);
    free(b_host);
    free(c_host);

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