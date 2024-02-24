#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:serial construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int sum = 0;

    // Initialize array
    for(int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    // Compute sum of array elements
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += a[i];
    }

    // Check if sum is correct
    int expected_sum = (n * (n + 1)) / 2;
    if(sum != expected_sum) {
        err = 1;
    }

    free(a);
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