#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
	int err = 0;
	srand(SEED);
	int sep = 10;
	real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
	real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
	real_t * c = (real_t *)malloc(n * sizeof(real_t));
	real_t * d = (real_t *)malloc(n * sizeof(real_t));
	real_t temp = 0;

	for (int x = 0; x < 10 * n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
	}
	for (int x = 0; x < 10; ++x){
		c[x] = rand() / (real_t)(RAND_MAX / 10);
		d[x] = 0.0;
	}

	#pragma acc data copyin(a[0:10*n], b[0:10*n]) copyin(c[0:10]) copyout(d[0:10])
	{
		#pragma acc parallel loop collapse(2) private(temp)
		for (int x = 0; x < 10; ++x){
			temp = 0;
			for (int y = 0; y < n; ++y){
				temp += a[x * n + y] + b[x * n + y];
			}
			d[x] = temp;
		}
	}

	for (int x = 0; x < 10; ++x){
		for (int y = 0; y < n; ++y){
			if (fabs(d[x]) > PRECISION){
				err += 1;
			}
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