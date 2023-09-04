#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
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

int acc_wait(int wait_arg){
    // Check if the wait_arg is a valid async-argument
    if (wait_arg < 0 || wait_arg >= NUM_ASYNC_QUEUES){
        return 1;
    }

    // Wait for all asynchronous operations on the specified async queue to complete
    for (int i = 0; i < NUM_ASYNC_QUEUES; i++){
        if (async_queues[i].async_arg == wait_arg){
            async_queues[i].async_wait();
        }
    }

    return 0;
}

int acc_wait_device(int wait_arg, int dev_num){
    // Check if the wait_arg is a valid async-argument
    if (wait_arg < 0 || wait_arg >= NUM_ASYNC_QUEUES){
        return 1;
    }

    // Check if the dev_num is a valid device number
    if (dev_num < 0 || dev_num >= NUM_DEVICES){
        return 1;
    }

    // Wait for all asynchronous operations on the specified async queue to complete
    for (int i = 0; i < NUM_ASYNC_QUEUES; i++){
        if (async_queues[i].async_arg == wait_arg && async_queues[i].dev_num == dev_num){
            async_queues[i].async_wait();
        }
    }

    return 0;
}

int acc_wait_all(){
    // Wait for all asynchronous operations on all async queues to complete
    for (int i = 0; i < NUM_ASYNC_QUEUES; i++){
        async_queues[i].async_wait();
    }

    return 0;
}

int acc_wait_all_device(int dev_num){
    // Check if the dev_num is a valid device number
    if (dev_num < 0 || dev_num >= NUM_DEVICES){
        return 1;
    }

    // Wait for all asynchronous operations on all async queues to complete
    for (int i = 0; i < NUM_ASYNC_QUEUES; i++){
        if (async_queues[i].dev_num == dev_num){
            async_queues[i].async_wait();
        }
    }

    return 0;
}