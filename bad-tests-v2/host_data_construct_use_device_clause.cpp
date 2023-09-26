#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    data *a = (data *)malloc(n * sizeof(data));
	private *b = (private *)malloc(n * sizeof(private));

    //host data construct with use_device clause
    #pragma acc data create(a[0:n]) copy(b[0:n])
    {
        #pragma acc host_data use_device(a[0:n])
        {
            #pragma acc parallel loop
            for (int x = 0; x < n; ++x){
                a[x].a = 1.0;
                a[x].b = a[x].a + 1.0;
                b[x].c = a[x].a / 2;
            }
        }
        stable(a, b, is_host);
    }

    for (int x = 0; x < n; ++x){
        a[x].a = 1.0;
        a[x].b = a[x].a + 1.0;
    }
    stable(a, b, n, is_device);

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