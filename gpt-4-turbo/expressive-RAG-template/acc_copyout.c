#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc_copyout,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 10;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));

    // Initialize arrays
    for(int i = 0; i < size; ++i){
        a[i] = i;
        b[i] = 0;
    }

    // Use OpenACC to modify 'a' array in the device
    #pragma acc data copy(a[0:size]) 
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            a[i] += 10; // modify data in the device
        }

        // Simulating the acc_copyout effect
        #pragma acc exit data copyout(a[0:size])
    }

    // Check if modifications are reflected in the host array
    for(int i = 0; i < size; ++i){
        if(a[i] != i + 10){
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

    failcode = test1();

    if(failcode != 0){
        printf("Test FAILED with %d errors.\n", failcode);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}