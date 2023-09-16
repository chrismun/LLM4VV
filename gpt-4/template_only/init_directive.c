#include <stdio.h>
#include <openacc.h>

int test1(){
    int err = 0;

#pragma acc init
    {
        // If the implementation properly supports 'init', this will not cause any issues.
        int a[10];
#pragma acc parallel loop
        for (int i = 0; i < 10; ++i) {
            a[i] = 2 * i;
        }
    }

    return err;
}

int main(){
    int failcode = 0;

    for (int x = 0; x < 100; ++x){
        failcode += test1();
    }

    if (failcode > 0) {
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}