#include "acc_testsuite.h"
#ifndef T1
//T1:data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int toggle = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t data = 1.0;
    
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX/10);
        b[x] = 0.0;
    }
    #pragma acc enter data copyin(a[0:n])
    #pragma acc data present(a[0:n]) create(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }
    
    #pragma acc update device(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
            break;
        }
    }
    
    return err;
}
#endif

int main(){
    int failed = 0;
    int device_test_failed = 0;
    int unmanaged_test_failed = 0;
    int test_failed;
    int unmanaged_data;
    int unmanaged_present = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        #ifndef T1
        unmanaged_data = 0;
        #pragma acc deviceptr(accdata) present(accdata)
        {
            if (acc_is_present((acctype *)accdata, sizeof(acctype) * size, unmanaged_data)){
                unmanaged_present = 1;
            }
        }
        if (unmanaged_present == 1){
            unmanaged_data = 0;
        }
        unmanaged_present = 0;
        test_failed = 0;
        if (unmanaged_data == 0){
            test_failed = test_failed + test1();
        }
        if (test_failed != 0){
            unmanaged_test_failed += 1;
        }
        #endif
    }
    
    failed = failed + unmanaged_test_failed;
    if (failed != 0){
        return 1;
    }
    else{
        return 0;