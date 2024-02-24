#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int sum = 0;

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(sum)
    {
        #pragma acc parallel loop vector reduction(+:sum)
        for(int i = 0; i < N; i++) {
            sum += a[i] + b[i];
        }
    }

    int expected_sum = 0;
    for(int i = 0; i < N; i++) {
        expected_sum += 2*i;
    }

    if(sum != expected_sum) {
        err = 1;
    }

    free(a);
    free(b);

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