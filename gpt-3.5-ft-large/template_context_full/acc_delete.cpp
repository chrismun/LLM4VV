#include "acc_testsuite.h"
#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    for(int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 1;
        c[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n])
    #pragma acc update device(c[0:n])
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for(int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(c[0:n])

    for(int x = 0; x < n; ++x){
        if(c[x] != 1 && c[x] != (a[x] + b[x])){
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