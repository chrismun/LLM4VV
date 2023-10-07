#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/* T1:acc memcpy d2d, V:2.0-2.7 */
int test1(){
    int err = 0;
    srand(SEED);
    int* host_data_src = (int*)malloc(100 * sizeof(int));
    int* host_data_dest = (int*)malloc(100 * sizeof(int));

    // init source data on host
    for(int i = 0; i < 100; i++) {
        host_data_src[i] = rand();
    }
    
    acc_set_device_num(0,acc_get_device_type());
    acc_init(acc_get_device_type());

    int* device_data_src = acc_copyin(host_data_src, 100 * sizeof(int));
    int* device_data_dest = acc_copyin(host_data_dest, 100 * sizeof(int));
  
    acc_memcpy_d2d(device_data_dest, device_data_src, 100 * sizeof(int), 0, 0);

    acc_memcpy_to_device(host_data_dest, device_data_dest, 100 * sizeof(int));

    for (int i = 0; i < 100; i++){
        if(host_data_dest[i] != host_data_src[i]){
            err = 1;
            break;
        }
    }
    free(host_data_src);
    free(host_data_dest);
    acc_shutdown(acc_get_device_type());
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}