#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:kernels construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    int N = 100;
    int *a = (int*)malloc(N * sizeof(int));
    int sum = 0;

    // Initialize array
    for(int i = 0; i < N; i++) {
        a[i] = i + 1;
    }

    // Compute sum of array elements
    #pragma acc kernels copyin(a[0:N]) copy(sum)
    {
        sum = 0;
        for(int i = 0; i < N; i++) {
            sum += a[i];
        }
    }

    // Check if sum is correct
    int expected_sum = (N * (N + 1)) / 2;
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
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}