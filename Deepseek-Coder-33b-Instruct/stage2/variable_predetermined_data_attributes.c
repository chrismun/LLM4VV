#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    int i, j;
    int a[100], b[100];

    for(i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel loop copyin(a[0:100]) copyout(b[0:100])
    for(i = 0; i < 100; i++) {
        b[i] = a[i];
    }

    for(i = 0; i < 100; i++) {
        if(a[i] != b[i]) {
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