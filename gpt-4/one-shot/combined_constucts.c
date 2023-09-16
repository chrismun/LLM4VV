#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,V:1.0-2.7
int test1(){
    int n = 10000;
    int err = 0;
    srand(12345);
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (float)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > 0.0001){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int num_test_calls = 20;
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < num_test_calls; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}