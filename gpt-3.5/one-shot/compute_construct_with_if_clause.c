#include "acc_testsuite.h"
#ifndef T2
//T2:parallel,loop,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int loop = (int) (1.4 * n);
    int* a = (int *)malloc(n * sizeof(int));
    int* b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copy(b[0:n])
    {
        #pragma acc parallel loop num_gangs(2) if(n > 1000)
        for (int x = 0; x < loop; ++x){
            b[x] = a[x] + 1;
        }
    }

    for (int x = 0; x < loop; ++x){
        if(b[x] != 2){
            err += 1;
            break;
        }
    }

    for (int x = loop; x < n; ++x){
        if(b[x] != 0){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}