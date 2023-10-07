#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"
#pragma acc routine seq
int async_test(){
    redop_async_init();
    return !(redop_async_test());
}

int main(){
    failed = 0;
    int host_failed = 0;
    int device_failed = 0;
    for (int x = 0; x < 10; ++x){
        if (async_test() != 0){
            host_failed = 1;
        }
    }
    
    #pragma acc parallel num_gang(10) num_worker(32)
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            if (async_test() != 0){
                #pragma acc atomic
                    device_failed = 1;
            }
        }
    }
    
    if (host_failed == 0 && device_failed == 0){
        return 0;