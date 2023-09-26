#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[n];

    for (int x=0; x<n; ++x){
        a[x] = 0;
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop vector
            for (int x=0; x<n; ++x){
                a[x] = 1;
            }
        }
    }

    for (int x=0; x<n; ++x){
        if (fabs(a[x]-1) > PRECISION){
            err = 1;
        }
    }
    
    return err;
}
#endif

#ifndef T2
//T2: loop construct vector clause with reduction 
int test2(){
    int err = 0;
    srand(SEED);

    std::vector<int> a(n, 1);
    a[6] = 2;

    int reduction = 0;

    #pragma acc data copy(a[0:n])
    {

        #pragma acc loop vector reduction(+:reduction)
        for(int x=0; x<n; ++x){
            reduction += a[x];
        }
        
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    
    std::vector<int> passed(2, 1);
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    else{
        failcode = failcode - (1 << 0);
        passed.push_back(1);
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
    else{
        failcode = failcode - (1 << 1);
        passed.push_back(2);
    }
#endif
    return failcode;
}