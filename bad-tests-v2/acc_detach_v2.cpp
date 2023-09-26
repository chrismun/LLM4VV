#include "acc_testsuite.h"
#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
	int err = 0;
	srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc data copyout(c[0:n])
    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i) {
            c[i] = acc_deviceptr((void *) &c[i]);
        }
        #pragma acc loop
        for (int i = 0; i < n; ++i) {
            c[i] = a[i] + b[i];
        }
        #pragma acc loop
        for (int i = 0; i < n; ++i) {
            acc_detach_finalize(&c[i]);
        }
    }

	for (int i = 0; i < n; ++i) {
		if (fabs(c[i] - (a[i] + b[i])) > PRECISION) {
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