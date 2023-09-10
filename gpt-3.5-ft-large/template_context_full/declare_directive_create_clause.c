#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        c[x] = 0;
    }

    #pragma acc declare create(a[0:n], c[0:n])
    #pragma acc parallel loop
    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != a[x] + b[x]){
            err += 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    int flag = 0;
    
    if (flag != 0){
        failcode += (1 << 0);
    }
    
    return failcode;
}