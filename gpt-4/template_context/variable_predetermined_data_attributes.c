#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

//test function
int test1() {
    int err = 0;

    int loops = 1000;
    int counter[loops];
    for(int i = 0; i < loops; i++) {
        counter[i] = 0;
    }

    #pragma acc kernels loop
    for(int i = 0; i < loops; i++) {
        counter[i]++;
    }

    for(int i = 0; i < loops; i++) {
        if(counter[i] != 1) {
            printf("Error at %d counter = %d\n", i, counter[i]);
            err = 1;
        }
    }

    return err;
}

//main function
int main() {

    int failed;
    int loop_testing_cases = 10;
    failed = 0;

    for(int i = 0; i < loop_testing_cases; i++) {
        failed += test1(); //adding error per test
    }

    if(failed != 0) {
        printf("%d tests failed.\n", failed);
        return 1;
    }

    printf("All tests passed.\n");
    return 0;
}