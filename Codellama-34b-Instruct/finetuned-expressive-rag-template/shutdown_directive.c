#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c, n;
    n = 1000;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = rand() % n;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc enter data create(c[0:n])

    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    #pragma acc exit data copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
            break;
        }
    }

    #pragma acc shutdown

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