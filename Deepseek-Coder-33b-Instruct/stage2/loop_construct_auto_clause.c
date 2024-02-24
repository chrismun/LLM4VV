#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    int i, j;
    int *a, *b, *c;
    int size = 100;

    a = (int*)malloc(size * sizeof(int));
    b = (int*)malloc(size * sizeof(int));
    c = (int*)malloc(size * sizeof(int));

    for(i = 0; i < size; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:size], b[0:size]) copyout(c[0:size])
    {
        #pragma acc parallel loop auto
        for(i = 0; i < size; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for(i = 0; i < size; i++) {
        if(c[i] != 2*i) {
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}