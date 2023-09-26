#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct async conpute, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t false_margin = POW10_APPROX_EXP - 2;

    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[n];
    real_t * a_host = new real_t[n];
    real_t * b_host = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    for (int x = 0; x < n; ++x){
        #pragma acc serial async(x % 2)
        {
	TEST_UPDATE_FOR("async", n, a[x], b[x], c[x])
	    c[x] = a[x] + b[x];
	}
	TEST_UPDATE_DEVICE("async", n, c[x])
        #pragma acc update host(c[x:x+1]) async(x % 2)
    }
    
    loops_host;

    for (int x = 0; x < n; ++x) {
        if (fabs(TEST_UPDATE[x] - a_host[x]) > false_margin) {
            err++;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:serial,data,async,construct-independent,V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);

    real_t false_margin = POW10_APPROX_EXP - 2;

    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[n];
    real_t * a_host = new real_t[n];
    real_t * b_host = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        for (int x = 0; x < n; ++x){
            #pragma acc serial async(1)
            {
	 #pragma acc loop
                for(int y = 0; y < 2; y++)
                TEST_UPDATE_FOR_ASYNC(n, c[x], a[x], b[x], a, b, c, false_margin);
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc update host(c[0:n]) async(1)
        #pragma acc serial async(1)
            {};
    }


    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > n * false_margin){
            err += 2;
            break;
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
    return failcode;
}