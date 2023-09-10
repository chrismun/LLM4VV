#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
	int err = 0;
#ifndef host
    int isHost = 0;
    int* isHost_ptr = &isHost;
    #pragma acc parallel loop reduction(+:isHost)
    for (int x = 0; x < acc_get_num_devices(acc_get_device_type()); ++x){
        isHost = 1;
    }
#endif

    if (acc_get_device_type() == acc_device_none){
        return err;
    }
    real_t **hostdata = (real_t **)malloc(n * sizeof(real_t*));

    for (int x = 0; x < n; ++x){
        hostdata[x] = (real_t *)malloc(n * sizeof(real_t));
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            hostdata[x][y] = 1;
        }
    }

    real_t *a = (real_t *)malloc(n * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * n * sizeof(real_t));
    int errors = 0;
    #pragma acc data copy(a[0:n * n], b[0 :n * n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                b[x * n + y] = 2;
            }
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                a[x * n + y] = hostdata[x][y];
            }
        }
        acc_memcpy_to_device(a, hostdata[0], n * n * sizeof(real_t));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    hostdata[x][y] = a[x * n + y];
                }
            }
        }
        #pragma acc update(hostdata[0:n][0:n])
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                if (fabs(hostdata[x][y] - b[x * n + y]) > PRECISION){
                    errors += 1;
                }
            }
        }
        #pragma acc update(a[0: n * n])
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < n; ++y){
                hostdata[x][y] = a[x * n + y] * 2;
            }
        }
        #pragma acc exit data delete(a[0:n * n]) copyout(hostdata[0:n][0:n])
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(hostdata[x][y] - hostdata[x][y]) > 2 * PRECISION){
                errors += 1;
            }
        }
    }

    acc_free(a, n * n * sizeof(real_t));
    acc_free(b, n * n * sizeof(real_t));
    for (int x = 0; x < n; ++x){
        free(hostdata[x]);
    }
    free(hostdata);

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