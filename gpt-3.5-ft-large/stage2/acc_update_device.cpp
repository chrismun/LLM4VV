#include "acc_testsuite.h"
#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * a_copy = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(1 << 16);
        a_copy[x] = a[x];
    }

    #pragma acc enter data create(a[0:n])
   
    for (int x = 1; x < n; ++x){
        a[x] = a[x - 1] + a[x];
    }

    #pragma acc update device(a[0:n])
    
    for (int x = 0; x < n; ++x){
        if (abs(a[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n]))

    return err;
}
#endif

#ifndef T2
//T2: acc update self, V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(sizeof(int) * n);
    int * a_copy = (int *)malloc(sizeof(int) * n);

    for (int x = 0; x < n; ++x){
    a[x] = rand() / (real_t)(1 << 16);
    a_copy[x] = a[x];
    }

    #pragma acc enter data copyin(a[0:n])


    for (int x = 1; x < n; ++x){
        a[x] = a[x - 1] + a[x];
    }

    #pragma acc update self(a[0:n])


    for (int x = 0; x < n; ++x){
        if (abs(a[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n]))


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