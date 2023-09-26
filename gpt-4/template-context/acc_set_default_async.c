#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef N
#define N 100   
#endif

#ifndef T1
// T1: acc set default async
void test1() {

    int async_id = 1;     // Simply using some arbitrary async value
    
    float *a = (float*) malloc(sizeof(float) * N);
    float *b = (float*) malloc(sizeof(float) * N);
    float *c = (float*) malloc(sizeof(float) * N);

    #pragma acc data create(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels
        {
            for(int i = 0; i < N; i++) {
                a[i] = (float)i;
                b[i] = (float)i;
            }
        }

        acc_set_default_async(async_id);    // Setting default async queue

        #pragma acc kernels async
        {
            for(int i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }

        acc_wait(async_id); // Ensure completion of calculations before reading back to CPU

    }

    // Check results
    for(int i = 0; i < N; i++) {
        if(c[i] != i*2) {
            printf("Test Failed. c[%d]=%f expected %d\n", i, c[i], i*2);
            exit(1);
        }
    }
    
    free(a);
    free(b);
    free(c);
    
    printf("Test Passed\n");
}
#endif

int main() {
    test1();
    return 0;
}