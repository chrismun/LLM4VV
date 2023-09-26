#include <iostream>
#include <cstdlib>
#include "acc_testsuite.h"
#include "openacc.h"

#ifndef T1
/*T1:acc attach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = new int[10];
    int *device_ptr = new int[10];

    for (int i = 0; i < 10; i++) {
        host_ptr[i] = rand() % 100;
    }

    #pragma acc enter data copyin(host_ptr[0:10])
    #pragma acc enter data create(device_ptr[0:10])

    acc_attach(&host_ptr);
    acc_attach(&device_ptr);

    #pragma acc parallel present(host_ptr[0:10], device_ptr[0:10])
    {
        int idx = acc_thread_id();
        device_ptr[idx] = host_ptr[idx];
    }

    acc_detach(&host_ptr);
    acc_detach(&device_ptr);

    #pragma acc update host(host_ptr[0:10])

    for (int i = 0; i < 10; i++) {
        if (host_ptr[i] != device_ptr[i]) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(host_ptr[0:10])
    #pragma acc exit data delete(device_ptr[0:10])

    delete[] host_ptr;
    delete[] device_ptr;

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