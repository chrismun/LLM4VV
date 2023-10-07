#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device num, V:2.7-3.3
int test1(){
    int err = 0;
    int num_devices;
    int device_num;
    srand(SEED);

    #pragma acc enter data copyin(a[0:1])
    #pragma acc parallel
    {
        #pragma acc loop
        for(int i=0; i<10; i++)
            a[i] = i;
    }

    num_devices = acc_get_num_devices( acc_device_not_host );
    for( int i = 1; i <= num_devices; i++ )
    {
        acc_set_device_num( i, acc_device_default );
        device_num = acc_get_device_num( acc_device_default );
        if( device_num != i )
            err = 1;
    }

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