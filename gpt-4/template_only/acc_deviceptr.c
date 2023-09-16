#include <openacc.h>
#include <stdlib.h>

#ifndef T1
#define T1
#define SIZE 1000
#define DELTA 0.01
#define SEED 1234567
#define NUM_TEST_CALLS 10

double abs_val(double a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

void initialize(double* a, int size) {
    int i;
    for(i = 0; i < size; i++) {
        a[i] = (double)i / 2.0;
    }
}

int check(double* a, double* d_a, int size) {
    int i;
    double cpu_val, gpu_val, abs_err, rel_err;

    for(i = 0; i < size; i++) {
        cpu_val = a[i];
        gpu_val = d_a[i];
        abs_err = abs_val(cpu_val - gpu_val);
        rel_err = abs_err / abs_val(cpu_val);

        if(rel_err > DELTA) {
            return -1;
        }
    }
    return 0;
}

int test1() {
    double *a, *d_a;
    int i, err = 0;
    srand(SEED);

    a = (double*)malloc(SIZE * sizeof(double));

    initialize(a, SIZE);

    d_a = (double*)acc_copyin(a, SIZE * sizeof(double));

    #pragma acc parallel loop deviceptr(d_a)
    for(i = 0; i < SIZE; i++) {
        d_a[i] += 2.0;
    }

    acc_memcpy_from_device(a, d_a, SIZE * sizeof(double));

    err = check(a, d_a, SIZE);

    acc_delete(a, SIZE * sizeof(double));
    free(d_a);

    return err;
}
#endif /* T1 */

int main()
{
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
#endif /* T1 */

    return failcode;
}