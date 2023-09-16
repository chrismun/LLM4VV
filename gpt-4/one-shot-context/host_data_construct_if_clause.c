#include "acc_testsuite.h"
#ifndef T2
// T2:host_data,if_clause,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_device = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = 0;
    }

    int condition = 1; // Condition to trigger if clause

    #pragma acc data copyin (a_host[0:n]) copyout (b_device[0:n])
    {
        #pragma acc host_data use_device(a_host, b_device) if (condition)
        {
            #pragma acc parallel loop  
            for (int x = 0; x < n; ++x)
            {
                b_device[x] = a_host[x];
            }
        }
    }

    #pragma acc update host(b_host[0:n]) 

    for (int x = 0; x < n; ++x)
    {
        if (fabs(b_host[x] - a_host[x]) > PRECISION)
        {
            err++;
        }
    }
    
    free(a_host);
    free(b_device);
    free(b_host);
    return err;
}
#endif

int main(){
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    return failed;
}