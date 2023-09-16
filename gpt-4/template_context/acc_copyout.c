#include "acc_testsuite.h"
#include "openacc.h"

#ifndef T1
//Test for acc_copyout function, Version: 2.7-3.3
int test1(){
    int err = 0;
    int bytes = 5;
    int * data_arg = (int*) malloc(bytes * sizeof(int));
    srand(SEED);

    #pragma acc enter data create(data_arg[0:bytes])
  
    // Filling data on device
    #pragma acc parallel loop present(data_arg[0:bytes])
    for( unsigned i = 0; i < bytes; i++ ) {
        data_arg[i] = rand();
    }
   
    acc_copyout(data_arg, bytes * sizeof(int));

    // Verification of data on host after copyout
    for( unsigned i = 0; i < bytes; i++ ) {
        if(data_arg[i] <= 0) {
            err = 1;
        }
    }

    free(data_arg);
    return err;
}
#endif

#ifndef T2
//Test for acc_delete function, Version: 2.7-3.3
int test2(){
    int err = 0;
    int bytes = 5;
    int *data_arg = (int*) malloc(bytes * sizeof(int));

    #pragma acc enter data create(data_arg[0:bytes])

    acc_delete(data_arg, bytes * sizeof(int));
    
    // Check if data is deleted from device memory
    #pragma acc parallel loop present_or_copy(data_arg[0:bytes])
    for( unsigned i = 0; i < bytes; i++ ) {
        if(data_arg[i] != 0) {
            err = 1;
        }
    }

    free(data_arg);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed != 0){
        failcode += (1 << 1);
    }
#endif

    return failcode;
}