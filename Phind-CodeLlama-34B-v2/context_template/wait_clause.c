#include "acc_testsuite.h"
#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int num_devices = acc_get_num_devices(device_type);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = rand() % n;
        c[x] = 0;
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }

        #pragma acc update self(c[0:n]) wait

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
                err = 1;
            }
        }
    }

    free(a);
    free(b);
    free(c);

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