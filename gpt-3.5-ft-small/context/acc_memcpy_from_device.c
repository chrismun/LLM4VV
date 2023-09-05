#include "acc_testsuite.h"
#ifndef T1
#define V1 host_or_device_ptr
#else
#define V1 present_or_not
#endif

int acc_testsuite_test_kernel_3227_gang(int* passing) {
    int device_num = acc_get_device_num(acc_async_sync);
    int i, j;
    int * host_or_device_ptr;
    int * present_or_not = (int *)malloc(1);
    acc_create(host_or_device_ptr, sizeof(int)*devnum);
    present_or_not[0] = 1;
    #pragma acc enter data copyin(present_or_not[0:1]) create(host_or_device_ptr[0:devnum])
    #pragma acc parallel num_gangs(devnum)
    {
        #pragma acc loop gang
        for (i = 0; i < devnum; ++i){
            if (devnum > 1){
                *(present_or_not) = 1;
                if (i == devnum - 1){
                    for (j = 0; j < length % devnum; ++j){
                        host_or_device_ptr[i * length / devnum + j] = 1;
                    }
                    for (j = length % devnum; j < length / devnum; ++j){
                        host_or_device_ptr[i * length / devnum + j] = 100;
                    }
                }
                else{
                    for (j = 0; j < length / devnum; ++j){
                        host_or_device_ptr[i * length / devnum + j] = 100;
                    }
                }
            }
            else{
                for (j = 0; j < length; ++j){
                    host_or_device_ptr[j] = 1;
                }
            }
        }
    }
    for (i = 0; i < devnum; ++i){
        if (devnum > 1){
            if (*(present_or_not) == 1){
                for (j = 0; (j < (length / devnum)) && (host_or_device_ptr[i * (length / devnum) + j] == 1); ++j){
                    if (j == (length / devnum) - 1){
                        if (i == devnum - 1){
                            for (j = 0; j < length % devnum; ++j){
                                if (host_or_device_ptr[i * length / devnum + j] != 1){
                                    return 1;
                                    host_or_device_ptr[i * length / devnum + j];
                                }
                            }
                        }
                    }
                }
            }
            else{
                if (i == devnum - 1){
                    for (j = 0; j < length % devnum; ++j){
                        if (host_or_device_ptr[i * length / devnum + j] != 100){
                            return 1;
                            host_or_device_ptr[i * length / devnum + j];
                        }
                    }
                }
                else{
                    for (j = 0; j < length / devnum; ++j){
                        if (host_or_device_ptr[i * length / devnum + j] != 100){
                            return 1;
                            host_or_device_ptr[i * length / devnum + j];
                        }
                    }
                }
            }
        }
        else{
            int is_present = 0;
            for (j = 0; (j < length) && (host_or_device_ptr[j] == 1); ++j){
                if (j == length - 1){
                    is_present = 1;
                }
            }
            if (is_present == 0){
                return 1;
                host_or_device_ptr[i * length / devnum + j];
            }
        }
    }
    #pragma acc exit data delete(host_or_device_ptr[0:devnum])
    return 0;