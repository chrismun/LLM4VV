#include "acc_testsuite.h"
#ifndef T1
/*T1:acc create,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(n * sizeof(int));
    int *host_data = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x) {
        data[x] = rand() % n;
        host_data[x] = data[x];
    }

    int *device_data = (int *)acc_create(data, n * sizeof(int));
    if (device_data != data) {
        err = 1;
    }

    for (int x = 0; x < n; ++x) {
        if (device_data[x] != host_data[x]) {
            err = 1;
        }
    }

    acc_delete(device_data, n * sizeof(int));
    free(data);
    free(host_data);

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