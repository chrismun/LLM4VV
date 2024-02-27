#include "acc_testsuite.h"
#ifndef T1
// T1:routine,V:2.7-3.3
int vector_addition(int* a, int* b, int* c, int size);

#pragma acc routine seq
int vector_addition(int* a, int* b, int* c, int size){
    int errors = 0;
    #pragma acc parallel loop copyin(a[0:size],b[0:size]) copyout(c[0:size])
    for(int i = 0; i < size; i++){
        c[i] = a[i] + b[i];
    }
    for(int i = 0; i < size; i++){
        if (c[i] != a[i] + b[i]){
            errors += 1;
        }
    }
    return errors;
}

int test1(){
    int err = 0;
    int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    int *c = (int*)malloc(size * sizeof(int));

    srand(SEED);
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    err += vector_addition(a, b, c, size);

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