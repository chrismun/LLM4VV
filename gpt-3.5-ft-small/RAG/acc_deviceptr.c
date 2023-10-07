#include "acc_testsuite.h"
#ifndef T1
//T1:runtime/data,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    int device_type = acc_get_device_type(acc_get_device_num());
    if (device_type != acc_device_nvidia){
        return 0;
    }
    int* a = (int *)malloc(10 * n * sizeof(int));
    int* b = (int *)malloc(10 * n * sizeof(int));
    int * a_reptr;
    int * b_reptr;
    #pragma acc enter data copyin(a[0:10*n], b[0:10*n])
    #pragma acc data present(a[0:10*n], b[0:10*n]))
    {
        #pragma acc host_data use_device(a[0:10*n], b[0:10*n]))
        {
            a_reptr = acc_deviceptr((h_void *) a);
            b_reptr = acc_deviceptr((h_void *) b);
            int num_errors = 0;
            if (a_reptr != (int*) & a[0]){
                num_errors++;
            }
            if (b_reptr != (int*) & b[0]){
                num_errors++;
            }
            if (num_errors != 0){
                err += 1;
            }
        }
        #pragma acc parallel present(a,b)
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    a[x * n + y] += 1;
                    b[x * n + y] += 2;
                }
            }
        }
        #pragma acc host_data use_device(a[0:10*n], b[0:10*n]))
        {
            int* temp_a_reptr = acc_deviceptr((h_void *) a);
            int* temp_b_reptr = acc_deviceptr((h_void *) b);
            int num_errors = 0;
            if (temp_a_reptr != a_reptr){
                num_errors++;
            }
            if (temp_b_reptr != b_reptr){
                num_errors++;
            }
            if (num_errors != 0){
                err += 1;
            }
        }
    }
    #pragma acc exit data copyout(a[0:10*n], b[0:10*n])
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (a[x * n + y] != 1){
                err += 1;
            }
            if (b[x * n + y] != 2){
                err += 1;
            }
        }
    }
    return err;
}
#endif

#ifndef T2
//T2:runtime/data,construct-independent,V:2.5-2.7
int test2(){
    int err = 0;
    int device_type = acc_get_device_type(acc_get_device_num());
    if (device_type != acc_device_nvidia){
        return 0;