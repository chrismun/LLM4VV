#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *d_a;
    int num_elements = 256;

    a = (int *)malloc(num_elements * sizeof(int));
    for (int x = 0; x < num_elements; ++x){
        a[x] = x;
    }

    #pragma acc enter data copyin(a[0:num_elements])
    #pragma acc parallel present(a[0:num_elements])
    {
    }

    #pragma acc exit data delete(a[0:num_elements])

    free(a);

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