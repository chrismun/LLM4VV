#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));
    int *c = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop
        for(int i = 0; i < n; ++i){
            c[i] = a[i] + b[i];
        }
    }

    for(int i = 0; i < n; ++i){
        if(c[i] != a[i] + b[i]){
            err++;
        }
    }

    free(a);
    free(b);
    free(c);

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