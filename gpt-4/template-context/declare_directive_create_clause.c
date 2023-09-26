#include "acc_testsuite.h"
#ifndef T1 
// T1: declare directive create clause, V:2.7-3.3

int test1()
{
    int err = 0;
    srand(SEED);
    int vector_length = 10;
    float* host_array = (float*) malloc(vector_length * sizeof(float));
    float* compare_array = (float*) malloc(vector_length * sizeof(float));
    
    #pragma acc declare create(host_array[0:vector_length])

    for (int i = 0; i < vector_length; i++)
    {
        host_array[i] = rand() / (float)RAND_MAX;
        compare_array[i] = host_array[i];
    } 

    #pragma acc parallel present(host_array[0:vector_length])
    {
        #pragma acc loop
        for (int i = 0; i < vector_length; i++)
        {
            host_array[i] += 1;
        }
    }

    for (int i = 0; i < vector_length; i++)
        if (host_array[i] != compare_array[i] + 1)
        {
            err = 1;
        }
    
    free(host_array);
    free(compare_array);

    return err;
}
#endif

int main()
{
    int failcode = 0;

    #ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed += test1();
    }

    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}