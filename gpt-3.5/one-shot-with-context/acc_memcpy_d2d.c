#include "acc_testsuite.h"
#ifndef T1
// T1: memcpy/d2d,async
int test1(){
    int dev_num_dest, dev_num_src;
    void * data_arg_dest, * data_arg_src;
    size_t bytes;
    int async_arg_src;

    // Initialize data and devices
    size_t size = n * sizeof(real_t);
    real_t * host_data = (real_t *) malloc(size);
    real_t * dest_data = (real_t *) malloc(size);
    real_t * src_data = (real_t *) malloc(size);
    for (int i = 0; i < n; i++){
        host_data[i] = i;
    }
    dev_num_dest = acc_get_device_num(acc_device_nvidia);
    dev_num_src = acc_get_device_num(acc_device_host);
    acc_malloc(&data_arg_dest, size);
    acc_malloc(&data_arg_src, size);
    acc_memcpy_from_device(data_arg_src, host_data, size);

    // Perform d2d memcpy asynchronously
    acc_async_queue_t async_queue = acc_queue_create(acc_queue_cuda_stream);
    async_arg_src = acc_get_queue_native_handle(async_queue);
    acc_memcpy_d2d_async(data_arg_dest, data_arg_src, size, dev_num_dest, dev_num_src, async_arg_src);

    // Wait for the data transfer to complete
    acc_queue_wait(async_queue);

    // Copy the destination data to the host
    acc_memcpy_to_host(dest_data, data_arg_dest, size);

    // Verify the result
    int err = 0;
    for (int i = 0; i < n; i++){
        if (dest_data[i] != host_data[i]){
            err++;
            break;
        }
    }

    // Clean up
    acc_free(data_arg_dest);
    acc_free(data_arg_src);
    acc_queue_destroy(async_queue);
    free(host_data);
    free(dest_data);
    free(src_data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}