#include "acc_testsuite.h"
#ifndef T1
//T1:acc unmap data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    acc_create(c, n * sizeof(real_t));
	acc_create(d, n * sizeof(real_t));
	acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));

    #pragma acc data copyin(c[0:n]) present(a[0:n], b[0:n]) 
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] * b[x];
            }
        }
    }

    acc_unmap_data(a);
    acc_unmap_data(b);

    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += 1;
            }
        }
    }
    
	acc_copyout(c, n * sizeof(real_t));
    acc_delete(c);

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * b[x] + 1)) > 4){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}