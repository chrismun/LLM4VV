#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy array a to array b using OpenACC
    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) device_type(nvidia)
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
    }

    // Check the results
    for (int i = 0; i < n; i++) {
        if (b[i] != a[i]) {
            err++;
        }
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}