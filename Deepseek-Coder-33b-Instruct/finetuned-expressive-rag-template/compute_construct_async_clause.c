#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:compute construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    int a[100], b[100], c[100];

    // Initialize arrays
    for(int i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Create two tasks, one of which is async
    #pragma acc data copyin(a[0:100], b[0:100]) copyout(c[0:100])
    {
        #pragma acc parallel loop async
        for(int i = 0; i < 100; i++) {
            c[i] = a[i] + b[i];
        }

        // This task will not block the main thread
        #pragma acc parallel loop
        for(int i = 0; i < 100; i++) {
            if(c[i] != a[i] + b[i]) {
                err = 1;
                break;
            }
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