#include "acc_testsuite.h"
#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int * a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * b = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * c = (unsigned int *)malloc(n * sizeof(unsigned int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = rand() % n;
        c[x] = 0;
    }

    acc_create(c, n * sizeof(unsigned int));

    #pragma acc data copyin(a[0:n], b[0:n]) present(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    acc_delete(c, n * sizeof(unsigned int));

    for (int x = 0; x < n; ++x){
        if (c[x] != 0){
            return 1;
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