#include <cstdlib>
#include <cstring>
#include <cstdio>

#ifndef T1
//T1:acc memcpy device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    void* data_dev_dest = acc_malloc(1024);
    void* data_dev_src = acc_malloc(1024);

    // Initialize the data on the device
    for (int i = 0; i < 1024; i++) {
        ((char*)data_dev_dest)[i] = (char)rand();
        ((char*)data_dev_src)[i] = (char)rand();
    }

    // Copy the data from the device to the host
    acc_memcpy_device(data_dev_dest, data_dev_src, 1024);

    // Check that the data was copied correctly
    for (int i = 0; i < 1024; i++) {
        if (((char*)data_dev_dest)[i] != ((char*)data_dev_src)[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory on the device
    acc_free(data_dev_dest);
    acc_free(data_dev_src);

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