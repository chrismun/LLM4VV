#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,V:2.0-2.7
int test1(){
	int err = 0;
    int size = n * sizeof(real_t);

    real_t *a_host = (real_t *)malloc(size);
    real_t *b_host = (real_t *)malloc(size);
    real_t *c_host = (real_t *)malloc(size);

    for (int i = 0; i < n; ++i){
        a_host[i] = rand() / (real_t)(RAND_MAX / 10);
        b_host[i] = rand() / (real_t)(RAND_MAX / 10);
        c_host[i] = 0.0;
    }

    #pragma acc enter data copyin(a_host[0:n], b_host[0:n], c_host[0:n])

    #pragma acc parallel present(a_host[0:n], b_host[0:n], c_host[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            c_host[i] = a_host[i] + b_host[i];
        }
    }

    #pragma acc exit data copyout(c_host[0:n])

    #pragma acc update host(c_host[0:n])

    for (int i = 0; i < n; ++i){
        if (fabs(c_host[i] - (a_host[i] + b_host[i])) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(a_host[0:n], b_host[0:n], c_host[0:n])

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