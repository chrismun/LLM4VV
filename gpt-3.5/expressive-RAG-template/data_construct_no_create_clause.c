#include "acc_testsuite.h"
#ifndef T1
// T1: data construct no_create clause, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* a = (int*)malloc(N * sizeof(int));
    int* b = (int*)malloc(N * sizeof(int));
    int* c = (int*)malloc(N * sizeof(int));

    if (!a || !b || !c){
        printf("Error: unable to allocate memory\n");
        return 1;
    }

    for (int i = 0; i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0: N], b[0: N]) create(c[0: N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }

    for (int i = 0; i < N; i++){
        if (c[i] != a[i] + b[i]){
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