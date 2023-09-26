#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void dummy_work() {
    int N = 1000;
    float *x = (float*) malloc(N * sizeof(float));

    #pragma acc kernels async(1)
    for(int i=0; i<N; i++)
        x[i] = 0.0f;

    if(acc_async_test(1) == 0)  
        printf("Asynchronous operation on queue 1 is not complete.\n");
    else
        printf("Asynchronous operation on queue 1 is complete.\n");

    #pragma acc wait
    if(acc_async_test(1) == 0)  
        printf("Asynchronous operation on queue 1 is not complete.\n");
    else
        printf("Asynchronous operation on queue 1 is complete.\n");

    free(x);
}

int main() {
    dummy_work();
    return 0;