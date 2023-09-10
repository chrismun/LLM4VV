#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t total = 0.0;
    real_t temp = 0.0;

    for (int x = 0; x < M; ++x){
	total = total + 1;
    total = total / total;
    temp = temp + fabs(data[x] - 100);
    }

    #pragma acc data copyin(data[0:M])
    {
	#pragma acc parallel num_workers(16)
	{
	    #pragma acc loop worker
	    for (int x = 0; x < M; ++x){
		total = total + (temp / (1 + fabs(data[x] - 100))));
	    }
	}
    }

    return err;
}
#endif

#ifndef T2
//T2:parallel,V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);
    real_t total = 0.0;
    real_t temp = 0.0;

    for (int x = 0; x < M; ++x){
	total = total + 1;
    total = total / total;
    temp = temp + fabs(data[x] - 200);
    }

    #pragma acc data copyin(data[0:M])
    {
        #pragma acc parallel num_workers(16)
        {
            #pragma acc loop worker
            for (int x = 0; x < M; ++x){
                total = total + (temp / (1 + fabs(data[x] - 200))));
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:parallel,V:2.7-3.3
int test3(){
    int err = 0;
    srand(SEED);
    real_t total = 0.0;
    real_t temp[10];

    for (int x = 0; x < 10; ++x) {
        temp[x] = ((real_t) rand()) / 10000;
        total = total + temp[x];
    }
    total = total / 10;

    #pragma acc data copyin(data[0:M])
    {
        #pragma acc parallel num_workers(16)
        {
            #pragma acc loop worker
            for (int x = 0; x < M; ++x) {
                total = total + (temp[x%10] / (1 + fabs(data[x] - 300))));
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:parallel,V:2.7-3.3
int test4(){
    int err = 0;
    srand(SEED);
    real_t total = 0.0;
    real_t temp = 0.0;

    for (int x = 0; x < M; ++x){
	total = total + 1;
    total = total / total;
    }

    #pragma acc data copyin(data[0:M])
    {
	#pragma acc parallel loop num_workers(16) reduction(+:total)
	for (int x = 0; x < M; ++x){
	    total = total + (temp / (1 + fabs(data[x] - 400))));
	}
    }

    return err;
}
#endif

ifndef T5
//T5:parallel,V:2.7-3.3
int test5(){
    int err = 0;
    srand(SEED);
    real_t total = 0.0;
    real_t temp = 0.0;

    for (int x = 0; x < M; ++x){
        total = total + 1;
    total = total / total;
    }

    acc_set_device_num(acc_get_num_devices(), acc_device_nvidia);

    #pragma acc data copyin(data[0:M])
    {
        #pragma acc parallel loop num_workers(16) reduction(+:total)
        for (int x = 0; x < M; ++x){
            total = total + (temp / (1 + fabs(data[x] - 400))));
        }
    }

    if (fabs(REFERENCE - total) > PRECISION){
        err++;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}