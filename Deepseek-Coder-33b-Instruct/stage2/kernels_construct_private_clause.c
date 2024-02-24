#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100
#define SEED 1234
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:kernels construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int data[N];
    int sum = 0;
    int private_sum = 0;

    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100;
        sum += data[i];
    }

    #pragma acc kernels copyin(data[0:N]) copyout(private_sum)
    {
        private_sum = 0;
        #pragma acc loop reduction(+:private_sum)
        for (int i = 0; i < N; i++) {
            private_sum += data[i];
        }
    }

    if (sum != private_sum) {
        err = 1;
    }

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