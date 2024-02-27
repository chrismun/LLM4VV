#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t *restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t *restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t *restrict d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
	c[x] = 0;
	d[x] = 0;
    }
    
    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n], d[0:n])
    #pragma acc serial loop num_gangs(16)
    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }
    #pragma acc exit data copyout(c[0:n])
    #pragma acc parallel loop num_gangs(16)
    for (int x = 0; x < n; ++x){
        d[x] = a[x] + b[x] + c[x];
    }    
        
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
	    err += 1;
	}
	if (fabs(d[x] - (a[x] + b[x] + c[x])) > PRECISION) {
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
    return failcode;
}