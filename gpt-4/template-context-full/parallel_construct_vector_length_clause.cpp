#include "acc_testsuite.h"
#include <cmath>

#ifndef T1
/*T1:parallel construct vector_length clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 512;
    int *a, *b, *c;
    int n = vector_length * 4;

    a = new int[n];
    b = new int[n];
    c = new int[n];

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc parallel copyout(c[0:n]) copyin(a[0:n], b[0:n]) vector_length(vector_length)
    {
        #pragma acc loop worker
        for(int i = 0; i < n; i++){
            c[i] = a[i] * b[i];
        }
    }

    for (int i=0; i < n; i++) {
        if (c[i] != a[i] * b[i]) {
            err = 1;
        }
    }
    
    delete[] a;
    delete[] b;
    delete[] c;

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