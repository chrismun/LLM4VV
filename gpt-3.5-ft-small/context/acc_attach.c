#ifndef T1
//T1:runtime,async,construct-independent,V:2.7-2
//C1:runtime,async,construct-independent
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "test_loop.h"

int test(){
    int errors = 0;

    // Test before and after region for acc_attach(max-devnum=0)
    int before_errors = 0, after_errors = 0;

    int* devnum_ptr = (int *) malloc(sizeof(int) * 2);
    int host_value = 10;

    unsigned int size = 1024;
    int x_inc = 3;

    real_t * a = (double *)malloc(1024*1024* sizeof(real_t)); assert(a);
    data_init(a, size);


    int counter = 17;

    acc_attach_async(0, a, size * sizeof(real_t), 0);

    acc_present_or_copyin_async(a, size * sizeof(real_t), 0);
    host_value = increment(host_value, 1);

    devnum_ptr[0] = 0;
    if(acc_device_self(0)){
        errors += data_check(a, host_value * 2, size);
    }
    else{
        before_errors = data_test(a, 10,(host_value+1)/host_value,x_inc, size,1,devnum_ptr,1);
        if(before_errors) errors += before_errors;
    }

    host_value = increment(host_value, 1);

    devnum_ptr[0] = 0;
    devnum_ptr[1] = 1;
    if(acc_device_self(0)){
        acc_attach((void **)&counter, 4, devnum_ptr);
        counter = increment(counter, 1);
        devnum_ptr[0] = 1;
        acc_attach((void **)&counter, 4, devnum_ptr);

        if(counter != (2 * host_value)){
            after_errors += 1;
        }
        host_value = counter;
    }
    else if(acc_device_self(1)){
        after_errors = data_test(a, 20,(host_value+1)/host_value,x_inc, size,1,devnum_ptr,1);

        devnum_ptr[0] = 0;
        acc_attach((void **)&counter, 4, devnum_ptr);
        counter = increment(counter, 1);
        devnum_ptr[0] = 1;
        acc_attach((void **)&counter, 4, devnum_ptr);
        if(counter != (2 * host_value)){
            after_errors += 1;
        }
    }
    else{
        devnum_ptr[0] = 0;
        after_errors = data_test(a, 10,(host_value+1)/host_value,x_inc, size,1,devnum_ptr,1);
        host_value = (real_t)a[0];
        devnum_ptr[0] = 1;
        int after_errors2 = data_test(a, 20,(host_value+1)/host_value,x_inc, size,1,devnum_ptr,1);
        if(after_errors2) after_errors += after_errors2;

        devnum_ptr[0] = 1;
        acc_attach((void **)&counter, 4, devnum_ptr);
        devnum_ptr[0] = 0;
        int after_errors3 = data_test(a, 10,(counter+1)/host_value,x_inc, size,1,devnum_ptr,1);
        if(after_errors3) after_errors += after_errors3;
        counter = increment(counter, 1);
        devnum_ptr[0] = 1;
        acc_attach((void **)&counter, 4, devnum_ptr);
        if(counter != (2 * host_value)){
            after_errors += 1;
        }
        host_value = counter;
    }
    acc_detach_async(0, a);
    acc_detach_if_present_async(a, 0);
    devnum_ptr[0] = 0;
    after_errors += data_test(a, 10,(host_value+1)/host_value,x_inc, size,1,devnum_ptr,1);

    if(before_errors){
        printf("Test attach_dev_ptr_before_compute failed with %d errors on device 1\n", before_errors);
    }
    if(after_errors){
        printf("Test attach_dev_ptr_after_compute failed with %d errors\n", after_errors);
    }
    errors += before_errors;
    errors += after_errors;
    assert_host(errors);
    return errors;
}