#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
int test1()
{
    int err = 0;
    int n = 100;
    float* a_host = (float*)malloc(n * sizeof(float));
    float* a_device = (float*)malloc(n * sizeof(float));
  
    srand(SEED);
    for (int i = 0; i < n; ++i)
        a_host[i] = rand();

    #pragma acc data copy(a_device[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i)
            a_device[i] = a_host[i] + 1.0;
    }

    for (int i = 0; i < n; ++i)
        if (a_device[i] != a_host[i] + 1.0)
            err = 1;
  
    free(a_host);
    free(a_device);
  
    return err;
}
#endif

int main()
{
    int failcode = 0;
    int failed;
        
#ifndef T1
    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed = failed + test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
    
    return failcode;
}