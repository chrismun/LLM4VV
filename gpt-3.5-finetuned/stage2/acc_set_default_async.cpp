#include "acc_testsuite.h"
#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;

    if (acc_get_device_type() != acc_device_none){    
        srand(SEED);
        unsigned int* a = (unsigned int *)malloc(n * sizeof(unsigned int));
        unsigned int* b = (unsigned int *)malloc(n * sizeof(unsigned int));
        real_t start = 0;
        real_t end = 0;

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (unsigned int)(RAND_MAX / 10);
            b[x] = 0;
        }

        acc_set_device_type(acc_get_device_type());
        acc_set_default_async(1);

        #pragma acc data copyin(a[0:n]) present(b[0:n])
        {
            start = get_time();
            #pragma acc parallel async
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] = a[x];
                }
            }
            acc_wait(1);
            end = get_time();
        }

        acc_set_default_async(acc_async_noval);

        #pragma acc data copyin(a[0:n]) present(b[0:n])
        {
            #pragma acc parallel async
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] += a[x];
                }
            }
            #pragma acc parallel async(1) wait(2)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] += a[x];
                }
            }
            #pragma acc enter data copyin(b[0:n]) async(2)
            #pragma acc parallel present(b[0:n]) async(1)
            {
                #pragma acc loop
                for(int x = 0; x < n; ++x){
                    b[x] += b[x];
                }
            }
            #pragma acc wait(1)
            #pragma acc exit data copyout(b[0:n]) delete(b[0:n]) async(2)
        }

        for (int x = 0; x < n; ++x){
            if (a[x] != b[x]){
                err += 1;
            }
        }

        for (int x = 0; x < n; ++x){
            if (a[x] * 4 != b[x]){
                err += 1;
            }
        }

        if (acc_on_host(b)){
            for (int x = 0; x < n; ++x){
                if (a[x] * 2 != b[x]){
                    err += 1;
                }
            }
        }

        free(a);
        free(b);
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