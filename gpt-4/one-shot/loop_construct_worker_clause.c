#include "acc_testsuite.h"
#include "openacc.h"
#include <math.h>

#ifndef T1
//T1:loop,worker,V:2.5-2.7
unsigned int test1()
{
    unsigned int err = 0;

    srand(SEED);
    long h_n;
    int gang_num = 10;
    int worker_num = 64;
    acc_device_t devtype = acc_get_device_type();
  
    real_t * h_a = (real_t *)malloc(n * sizeof(real_t));
    real_t total = 0, t_total = 0, r_total = 0;

    for (long x = 0; x < n; ++x){
        h_a[x] = 0;
    }

    #pragma acc data copy(h_a[0:n])
    {
        #pragma acc parallel num_gangs(gang_num) vector_length(worker_num) copy(h_n)
        {
            h_n = n;
        }

        #pragma acc parallel loop worker(num_workers) gang worker
        for (long x = 0; x < h_n; ++x){
            h_a[x] = 1;
            #pragma acc loop seq reduction(+:total)
            for (long y = 0; y < 10; ++y){
                total += y;
            }
        }
    }
    
    t_total = (h_n*10.*(10.-1))/2.; // expected reduction result
    r_total = n; // expected assigned value

    if (fabs(total - t_total) > PRECISION) err += 1;
    for (long x = 0; x < h_n; ++x) {
        if (fabs(h_a[x] - r_total) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
 
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}