#include "acc_testsuite.h"
#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int* original_data = (unsigned int *)malloc(10 * n * sizeof(unsigned int));
    unsigned int* data = (unsigned int*)malloc(n * sizeof(unsigned int));
    unsigned int* a = (unsigned int *)malloc(10 * sizeof(unsigned int));

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x] = 0;
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        original_data[x] = (unsigned int) rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:10]) create(data[0:n])
        

    #pragma acc data copy(data[0:n]) present(a[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10 * n; ++x){
                data[x] = original_data[x] + a[x % 10];
            }
        }
    }

    #pragma acc exit data  copyout(a[0:10]) delete(data[0:n])

    for (int x = 0; x < 10; ++x){
        if (a[x] != original_data[x]){
            err = 1;
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