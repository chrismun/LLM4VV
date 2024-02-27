#include "acc_testsuite.h"
#ifndef T1
const size_t n = 10;
const size_t m = 10;
int test1(){
	int err = 0;
	srand(SEED);
	int * a = (int *)malloc(n * m * sizeof(int));
	int * b = (int *)malloc(n * m * sizeof(int));
	int * c = (int *)malloc(n * m * sizeof(int));

	for (int x = 0; x < n * m; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}

	#pragma acc data copyin(a[0:n*m], b[0:n*m]) copyout(c[0:n*m])
	{
		#pragma acc serial loop independent
		for (int x = 0; x < n; ++x){
			#pragma acc parallel loop independent
			for (int y = 0; y < m; ++y){
				c[x * m + y] = a[x * m + y] + b[x * m + y];
			}
		}
	}

	for (int x = 0; x < n; ++x){
		for (int y = 0; y < m; ++y){
			if (fabs(c[x * m + y] - (a[x * m + y] + b[x * m + y])) > PRECISION){
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