#include "acc_testsuite.h"
#ifndef T1
// T1: host_data, use_device, V:2.5-2.7
_Bool host_data_if_present_test() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device = (real_t *)acc_create(a, n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc host_data use_device(a) if_present
    {
        real_t *a_ptr;
        acc_memcpy_to_device(a_device, a, n * sizeof(real_t));
        a_ptr = a;

        #pragma acc parallel loop present(a_ptr[0:n])
        for (int x = 0; x < n; ++x) {
            a_ptr[x] = 2 * a_ptr[x];
        }

        acc_memcpy_from_device(a, a_device, n * sizeof(real_t));
        #pragma acc exit data delete(a[0:n])

        for (int x = 0; x < n; ++x) {
            if (fabs(2 * a[x] - a_device[x]) > PRECISION) {
                return 1;
            }
        }
    }
    return err;
}
#endif

int main() {
    int failed = 0;
    #ifndef T1
    failed += host_data_if_present_test();
    #endif
    printf(failed ? "Test failed\n" : "Test passed\n");
    return failed;
}