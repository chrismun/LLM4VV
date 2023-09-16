#include "acc_testsuite.h"

// Function to test parallel loop
#ifndef T_PARALLEL_LOOP
//T_PARALLEL_LOOP: combined constucts, V:2.7-3.3
int test_parallel_loop(){
    int err = 0;
    int array[1024];

    #pragma acc parallel loop 
    for(int i=0; i<1024; i++){
        array[i] = i;
    }

    for(int i=0; i<1024; i++){
        if(array[i] != i){
            err = 1;
            break;
        }
    }

    return err;
}
#endif

// Function to test serial loop
#ifndef T_SERIAL_LOOP
//T_SERIAL_LOOP: combined constucts, V:2.7-3.3
int test_serial_loop(){
    int err = 0;
    int array[1024];

    #pragma acc serial loop 
    for(int i=0; i<1024; i++){
        array[i] = i;
    }

    for(int i=0; i<1024; i++){
        if(array[i] != i){
            err = 1;
            break;
        }
    }

    return err;
}
#endif

// Function to test kernels loop
#ifndef T_KERNELS_LOOP
//T_KERNELS_LOOP: combined constucts, V:2.7-3.3
int test_kernels_loop(){
    int err = 0;
    float array[1024];

    #pragma acc kernels loop 
    for(int i=0; i<1024; i++){
        array[i] = i * 0.5;
    }

    for(int i=0; i<1024; i++){
        if(array[i] != (i * 0.5)){
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

#ifndef T_PARALLEL_LOOP
    failed = test_parallel_loop();
    if (failed != 0){
        printf("Parallel loop test failed!\n");
        failcode = failcode + (1 << 0);
    }
#endif

#ifndef T_SERIAL_LOOP
    failed = test_serial_loop();
    if (failed != 0){
        printf("Serial loop test failed!\n");
        failcode = failcode + (1 << 1);
    }
#endif

#ifndef T_KERNELS_LOOP
    failed = test_kernels_loop();
    if (failed != 0){
        printf("Kernels loop test failed!\n");
        failcode = failcode + (1 << 2);
    }
#endif

    return failcode;
}