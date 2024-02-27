#include "acc_testsuite.h"

#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    unsigned int* a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * b = (unsigned int *)malloc(n * sizeof(unsigned int));;

    if (a == NULL || b == NULL){
        err = 1;
    }
    unsigned int * c = (unsigned int *)malloc(n * sizeof(unsigned int));

    for (int x = 0; x < n; ++x) {
        a[x] = 0;
        b[x] = 1;
        c[x] = 0;
    }
    acc_copyin(a, n * sizeof(unsigned int));
    acc_copyin(b, n * sizeof(unsigned int));
    #pragma acc data deviceptr(c) 
    {
            #pragma acc parallel loop
            for(int x = 0; x <n; ++x){
                c[x] =  a[x] + b[x];
            }
    }
    int * a_ptr = reinterpret_cast<int>(acc_deviceptr(a));
    
    #pragma acc parallel loop deviceptr(a)
    for (int x = 0; x < n; ++x){
        a_ptr[x] = c[x];
    }
    
    acc_copyout(a, n * sizeof(int));
    
    for (int x = 0; x < n; ++x){
        if (a[x] != b[x]){
            err += 1;
        }
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