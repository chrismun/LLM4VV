#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int a[N], b[N], c[N];

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Parallelize the loop
    #pragma acc parallel loop
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Sequentially execute the loop
    #pragma acc loop seq
    for (int i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
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
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}