c
#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_TEST_CALLS 100
#define SEED 12345

#ifndef T1
// T1:routine directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test the gang clause
    int gang_dim = rand() % 3 + 1;
    #pragma acc routine gang(gang_dim)
    void gang_func(){
        // Do something
    }
    gang_func();

    // Test the worker clause
    #pragma acc routine worker
    void worker_func(){
        // Do something
    }
    worker_func();

    // Test the vector clause
    #pragma acc routine vector
    void vector_func(){
        // Do something
    }
    vector_func();

    // Test the seq clause
    #pragma acc routine seq
    void seq_func(){
        // Do something
    }
    seq_func();

    // Test the bind clause
    #pragma acc routine bind(bind_func)
    void bind_func(){
        // Do something
    }
    bind_func();

    // Test the device_type clause
    #pragma acc routine device_type(device_type_list)
    void device_type_func(){
        // Do something
    }
    device_type_func();

    // Test the nohost clause
    #pragma acc routine nohost
    void nohost_func(){
        // Do something
    }
    nohost_func();

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