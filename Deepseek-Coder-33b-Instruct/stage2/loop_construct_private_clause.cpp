#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(0));

    const int n = 100;
    int a[n], b[n], c[n], tmp;

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        b[i] = rand() % 100;
        c[i] = rand() % 100;
    }

    #pragma acc data copyin(b, c) copyout(a)
    {
        #pragma acc parallel loop gang worker private(tmp)
        for (int k = 0; k < n; ++k) {
            tmp = b[k] + c[k];
            #pragma acc loop vector
            for (int i = 1; i < n; ++i) {
                a[i] = a[i] + tmp;
            }
        }
    }

    // Check the results
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i] + c[i] + tmp) {
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
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}