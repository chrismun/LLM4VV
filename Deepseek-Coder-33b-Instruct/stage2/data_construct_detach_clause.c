#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int *ptr = (int*)malloc(N * sizeof(int));

    // Initialize the array
    for (int i = 0; i < N; i++) {
        ptr[i] = i;
    }

    // Copy the array to the device
    #pragma acc data copyin(ptr[0:N])
    {
        // Detach the array
        #pragma acc exit data detach(ptr[0:N])
    }

    // Check if the array is still accessible
    for (int i = 0; i < N; i++) {
        if (ptr[i] != i) {
            err = 1;
            break;
        }
    }

    free(ptr);

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