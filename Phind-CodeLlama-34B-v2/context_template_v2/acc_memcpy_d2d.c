#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_num_dest = 0;
    int dev_num_src = 0;
    size_t bytes = 1024;
    int async_arg_src = 0;
    int *data_arg_dest, *data_arg_src;

    data_arg_dest = (int *)malloc(bytes);
    data_arg_src = (int *)malloc(bytes);

    for (int i = 0; i < bytes / sizeof(int); i++) {
        data_arg_src[i] = i;
    }

    #pragma acc enter data copyin(data_arg_src[0:bytes/sizeof(int)])
    #pragma acc enter data create(data_arg_dest[0:bytes/sizeof(int)])

    #pragma acc data present(data_arg_dest, data_arg_src)
    {
        acc_memcpy_d2d(data_arg_dest, data_arg_src, bytes, dev_num_dest, dev_num_src);
    }

    #pragma acc exit data copyout(data_arg_dest[0:bytes/sizeof(int)])

    for (int i = 0; i < bytes / sizeof(int); i++) {
        if (data_arg_dest[i] != i) {
            err = 1;
            break;
        }
    }

    free(data_arg_dest);
    free(data_arg_src);

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