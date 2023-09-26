#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#define N 1000
#define NUM_TEST_CALLS 100

// test1: acc_wait_async
int test1() {
    int *a = (int*) malloc(sizeof(int)*N);
    int *b = (int*) malloc(sizeof(int)*N);
    int err = 0;

    // initialize host arrays
    for(int i=0; i<N; i++) {
        a[i] = rand();
        b[i] = 0;
    }

    int asyncId = acc_async_test_all();

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels async(asyncId)
        {
          for(int i=0; i<N; i++) {
            b[i] = a[i];
          }
        }        
    }

    // wait for all async operations to complete
    acc_wait_async(asyncId);

    // check if the values in array b are correct
    for(int i=0; i<N; i++) {
        if(a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    // free the memory
    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    srand(2014);

    failed = 0;
    for(int x=0; x<NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
      printf("PASSED\n");
    } else {
      printf("FAILED\n");
    }
    
    return failcode;
}