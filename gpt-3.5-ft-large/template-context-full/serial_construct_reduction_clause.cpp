#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

  real_t * a = new real_t[n];
    uint32_t * a_desc = new uint32_t[4 * n];
    real_t * b = new real_t[n];
    real_t c_cop = 0.0;
    real_t c = 10.0;
    real_t temp = 0.0;
    int errors = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    
    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:1]) copyout(a_desc[0:4*n]) 
    
    a_desc_create(a_desc, a, 0, true);
    a_desc_create(a_desc, b, 2, true);
    
      #pragma acc serial copyin(a_desc[0:4*N])
    {
        #pragma acc loop worker reduction(+:c_cop)
        for (int x = 0; x < n; ++x){
            c_cop += a[x] * b[x];
        }
        if (fabs(c_cop - c) > PRECISION * n){
            errors = 1;
        }

        #pragma acc loop independent
        for (int x = 0; x < n; ++x){
            temp = a_desc_lookup(a_desc, a[x], 0, true) * a_desc_lookup(a_desc, b[x], 2, true);
            a_desc_update(a_desc, temp, a[x], 0, true);
        }

        #pragma acc loop worker reduction(+:c_cop)
        for (int x = 0; x < n; ++x){
            c_cop += a[x] * b[x];
        }
        if (fabs(c_cop - (c + c_cop)) > n * PRECISION){
            errors += 2;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:serial,data,references,loopconstructs,construct-independent,V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c_host = new real_t[n];
    int dev = 1;
    #pragma acc set device_num(dev)

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c_host[x] = -5;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc serial
        {
            #pragma acc loop gang worker vector
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c_host[x] - (a[x] + b[x])) > PRECISION){
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}