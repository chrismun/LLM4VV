#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef T2
// T2: loop,parallel, V:1.0-3.1
int test_independent_loop(){
    int err = 0;
    int n = 10000;
    float *input = (float *)malloc(n * sizeof(float));
    float result = 0.0;
    float expectedResult = 0.0;

    // Initialize input data
    for (int i = 0; i < n; ++i){
        input[i] = 1.0f; // Simple case, summing ones
        expectedResult += input[i];
    }

    #pragma acc data copyin(input[0:n])
    {
        #pragma acc parallel loop independent reduction(+:result)
        for (int i = 0; i < n; ++i){
            result += input[i];
        }
    }

    if (fabs(result - expectedResult) > 1e-5){
        err += 1;
        printf("Test failed: Result = %f, Expected = %f\n", result, expectedResult);
    } else {
        printf("Test passed: Result = %f, Expected = %f\n", result, expectedResult);
    }

    free(input);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = test_independent_loop();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}