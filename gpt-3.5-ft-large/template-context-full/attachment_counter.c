#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *has_attached = (int *)malloc(n * sizeof(int));
    int attach_count;
    int device = acc_get_device_type();

    if(device == acc_device_none){
        return err;
    }

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        has_attached[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    for (int x = 0; x < n; ++x){
        #pragma acc kernels
        {   
            a[x] = a[x] + 1;
        }
    }
    #pragma acc exit data delete(a[0:n]) copyout(b[0:n])

    for (int x = 0; x < n; ++x){
        if (b[x] != 3){
            err = 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (has_attached[x]){
            for (int y = 0; y < x; ++y){
                if (a[x] == a[y]){
                    attach_count = *(ptr[1] + ((long long int) (ptr - a) * n + (x + 1) * size) / size / n);
                    if (attach_count != 1){
                        err = 1;
                        break;
                    }
                }
            }
            has_attached[x] = 1;
        }
    }
    #pragma acc exit data detach(a[0:n])
    
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