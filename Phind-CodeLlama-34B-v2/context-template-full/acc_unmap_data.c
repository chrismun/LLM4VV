#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc unmap data,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() % n;
    }

    acc_map_data(host_data, n * sizeof(int));
    acc_memcpy_to(device_data, host_data, n * sizeof(int));
    acc_unmap_data(host_data);

    int *host_data_2 = (int *)malloc(n * sizeof(int));
    acc_map_data(host_data_2, n * sizeof(int));
    acc_memcpy_from(host_data_2, device_data, n * sizeof(int));
    acc_unmap_data(host_data_2);

    for (int x = 0; x < n; ++x){
        if (host_data_2[x] != host_data[x]){
            err = 1;
            break;
        }
    }

    free(host_data);
    free(host_data_2);
    acc_free(device_data);

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