#include "acc_testsuite.h"

//T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 50;
    int* a = (int*)malloc(sizeof(int) * n);
    int* b = (int*)malloc(sizeof(int) * n);
    int target = rand() % n;

    for (int i = 0; i < n; ++i){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel loop firstprivate(target)
    for (int i = 0; i < n; ++i){
        if(i == target) 
            b[i] = a[target];
    }

    for(int i = 0; i < n; ++i) 
        if(i != target && b[i] != 0)
            err = 1;

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}