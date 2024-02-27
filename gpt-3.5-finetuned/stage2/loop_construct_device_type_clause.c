#include "acc_testsuite.h"
#ifndef T1
//T1:loop,construct,device_type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #if defined (_OPENACC)
		if (_OPENACC  != 201911)
			if (_OPENACC  != 201803)
				return err;
	#endif
	int _check_offload;
	_check_offload = 1;
	acc_create(_check_offload,0);
    #endif

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    int x = 1;
    #pragma acc loop device_type(x)
    for (int i = 0; i < n; ++i){
        c[i] = a[i] + b[i];
    }

    acc_shutdown(_check_offload);
    acc_shutdown(1);
    acc_shutdown(2);

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