#include "acc_testsuite.h"
#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
	int x;
    int err = 0;
    for (x = 0; x < n; ++x){
        err = err + host_data[x];
		}
    if (for)
        err = 1;

    return err;
}
#endif

#ifndef T2
//T2: acc async test,V:2.7-3.3
int test2(){
	int x;
    int err = 0;
		for (x = 0; x < NUM_ASYNC_QUEUES - 1; ++x){
        acc_init_test_device(host_data[x], acc_get_device_num(acc_get_device_type()), x);
		}
		acc_init_test_device(host_data[x], acc_get_device_num(acc_get_device_type()), 0);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
		int x;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}