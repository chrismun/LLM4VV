#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

   real_t multiply_reduction(real_t* a, real_t* b, int length, int nlap){
	int i, j;
	real_t returned = 0.0;

	for (i = 0; i < length; i++){
		a[i] = rand() / (real_t) RAND_MAX;
		b[i] = rand() / (real_t) RAND_MAX;
	}

        #pragma acc kernels create(a[0:length], b[0:length])
	for (nlap = 0; nlap < NLAPS; nlap++){
                #pragma acc loop seq
		for (i = 0; i < length; i++){
			a[i] = 0.0;
		}
                #pragma acc loop seq
		for (i = 0; i < length; i++){
			for (j = 0; j < length; j++){
				a[i] += b[i * length + j];
			}
		}
                #pragma acc loop seq
		for (i = 0; i < length; i++){
			for (j = 0; j < length; j++){
				a[i * length + j] = a[i] / length;
			}
		}
	}

	for (i = 0; i < length; i++){
		returned += a[i];
	}

	return returned;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}

int main(){
	int failcode, failed;
        failed = 0;
	for (int x = 0; x < NUM_TEST_CALLS; ++x){
		failed = failed + test1();
	}
	if (failed != 0){
		failcode = 1;
	} else {
		failcode = 0;
	}
	return failcode;
}