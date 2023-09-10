#include "acc_testsuite.h"
#ifndef T1
// T1: data construct no_create clause, V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
	
	const int size = 1000;
    float* a = new float[size];
    float* b = new float[size];

    // Initialize arrays
    for (int i = 0; i < size; i++) {
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
    }

    #pragma acc data no_create(a[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            b[i] = a[i] * 2.0f;
        }
    }

    // Validation
    for(int i = 0; i < size; ++i) {
        if(fabs(b[i] - a[i] * 2.0f) > 1e-5) {
            err = 1;
            break;
        }
    }
	
	delete[] a;
	delete[] b;
	
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}