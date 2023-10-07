#include "acc_testsuite.h"

//Test1:Checking implementation of "exit data delete" clause
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x]+2;
            }
        }
    }

    #pragma acc exit data delete(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a[x]+2)) > PRECISION){
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int fail=0;
    fail = test1();
    
    if (fail != 0){
        failcode=1;
    }
    return failcode;
}