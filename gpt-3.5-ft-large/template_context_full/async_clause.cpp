#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_devdata = acc_create(host, d_data, n * sizeof(real));
    #pragma acc target device(host) copyin(real_devdata[0:n]) 
    {
        #pragma acc parallel loop present(real_devdata[0:n]) async(1)
        for (int x = 0; x < n; ++x){
            real_devdata[x] = -1.0;
        }
    }
    #pragma acc exit data copyout(real_devdata[0:n])
    for (int x = 0; x < n; ++x){
        if(fabs(real_devdata[x] - data[x]) > PRECISION){
            err += 1 + x;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:async clause,V:2.7-3.0
int test2(){
    int err = 0;
    srand(SEED);
    real_devdata = acc_create(host, d_data, n * sizeof(real));
    for (int x = 0; x < n; ++x){
        d_data[x] = 0;
    }

    #pragma acc data copy(d_data[0:n]) copyout(real_devdata[0:n])
	{
	    #pragma acc serial async(0)
	    {
                #pragma acc loop
		            for (int x = 0; x < n; ++x){
		                    d_data[x] = 1;
		            }
	    }
	    #pragma acc serial async(1)
        {
            #pragma acc loop
			for (int x = 0; x < n; ++x){
				real_devdata[x] = d_data[x] * 4.5;
			}
		}
	}

    #pragma acc exit data copyout(real_devdata[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(real_devdata[x] / 4.5 - 1.f) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:async clause,V:2.7-2.5
int test3(){
    int err = 0;
    srand(SEED);
    real_devdata = acc_create(host, d_data, n * sizeof(real));
    for (int x = 0; x < n; ++x){
        d_data[x] = 0;
    }

    #pragma acc data copy(d_data[0:n]) copyout(real_devdata[0:n])
    {
        #pragma acc parallel async(0)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                real_devdata[x] = 1;
            }
        }
        #pragma acc serial async(0)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d_data[x] = 1;
            }
        }
    }

    #pragma acc exit data copyout(real_devdata[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(real_devdata[x] - 1) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif
#ifndef T4
//T4:async clause,V:2.7-2.5
int test4(){
    int err = 0;
    srand(SEED);
    real_devdata = acc_create(host, d_data, n * sizeof(real));
    for (int x = 0; x < n; ++x){
        d_data[x] = 0;
    }

    #pragma acc data copy(d_data[0:n]) copy(real_devdata[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                real_devdata[x] = 1;
            }
        }
        #pragma acc serial async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d_data[x] = real_devdata[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d_data[x] - 1) > PRECISION){
            err += 1;
        }
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
    return failcode;
}