#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t *a_host_data = hostdata;
    real_t *b_host_data = &(hostdata[n]);
    real_t *c_host_data = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(hostdata[0:2*n])
    #pragma acc host_data use_device(hostdata[0:n]) if_present(a[0:n], b[0:n]) create(c_host_data[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c_host_data[x] = a[x] + b[x];
            }
        }
    }
    #pragma acc exit data copyout(hostdata[0:n]) 
    for (int x = 0; x < n; ++x){
        if (fabs(hostdata[x] - c_host_data[x]) > PRECISION){
            err += 1;
        }
    }

    int flag = 0;
    //checking the contents of c with hostdata
	for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            flag = 1;
        }
    }
    if (flag == 1){
        for (int x = 0; x < n; ++x){
            c[x] = 0;
        }
        #pragma acc enter data copyin(a[0:n], b[0:n]) create(hostdata[0:2*n])
        #pragma acc host_data use_device(hostdata[0:n]) if_present(a[0:n], b[0:n]) create(c_host_data[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c_host_data[x] = a[x] + b[x];
                }
            }
            #pragma acc update host(c_host_data[0:n])
        }
        #pragma acc exit data copyout(hostdata[0:n])
        for (int x = 0; x < n; ++x){
            if (fabs(c_host_data[x] - (a[x] + b[x])) > PRECISION){
                err += 1;
            }
        }
    }

    free(a);
    free(b);
    free(c);
    free(hostdata);
    free(c_host_data);

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