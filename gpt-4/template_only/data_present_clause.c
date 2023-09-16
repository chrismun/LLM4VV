#include "acc_testsuite.h"
#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int* host_data = (int*)malloc(10*sizeof(int));
    int* dev_data;
    acc_init(acc_device_default);

    for(int i = 0; i < 10; i++)
        host_data[i] = rand()%100;

    #pragma acc enter data copyin(host_data[0:10])

    dev_data = acc_deviceptr(host_data);
    if(dev_data == NULL)
        err = 1;
  
    #pragma acc exit data delete(host_data)
  
    acc_shutdown(acc_device_default);
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