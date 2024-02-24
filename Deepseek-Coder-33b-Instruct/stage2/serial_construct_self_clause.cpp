#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:serial construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 1000;
    int a[N], b[N], c[N];

    // Initialize arrays
    for(int i = 0; i < N; i++){
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Parallelize the loop
    #pragma acc parallel loop self(a, b, c)
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    // Check the results
    for(int i = 0; i < N; i++){
        if(c[i] != 2*i){
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}