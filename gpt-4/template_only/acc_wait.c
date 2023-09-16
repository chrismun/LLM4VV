#include "openacc.h"
#include "acc_testsuite.h"
#include <time.h> 
#include <stdlib.h>

#ifndef T1
#define T1
//T1:acc wait,V:2.7-3.3
int test1()
{
    int err = 0;
    srand(time(NULL));
    const int N = 100;
    float *x = (float *)malloc(N * sizeof(float));
    float *y = (float *)malloc(N * sizeof(float));

    #pragma acc parallel loop
    for(int i = 0; i < N; i++)
    {
        x[i] = (float)rand()/RAND_MAX;
    }

    #pragma acc wait

    #pragma acc parallel loop copyin(x[0:N]) copyout(y[0:N])
    for(int i = 0; i < N; i++)
    {
        y[i] = x[i] * 2.0f;
    }

    // Verification
    #pragma acc wait
    for(int i = 0; i < N; i++)
    {
        if(abs(y[i] - 2.0 * x[i]) > 1e-2f)
        err = 1;
    }

    free(x);
    free(y);

    return err;
}
#endif

int main()
{
    int failcode = 0;
#ifndef T1
    for (int x = 0; x < NUM_OF_REPEAT; ++x){
        int failed = test1();
        failcode += failed;
    }
#endif
    return failcode;
}