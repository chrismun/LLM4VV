#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_threads = num_gangs * num_workers;

    int* a = (int*)malloc(num_threads * sizeof(int));
    int* b = (int*)malloc(num_threads * sizeof(int));
    int* c = (int*)malloc(num_threads * sizeof(int));

    for (int x = 0; x < num_threads; ++x){
        a[x] = rand() % 100;
        b[x] = rand() % 100;
        c[x] = 0;
    }

    #pragma acc kernels num_gangs(num_gangs) num_workers(num_workers)
    {
        #pragma acc loop
        for (int x = 0; x < num_threads; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < num_threads; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
            break;
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