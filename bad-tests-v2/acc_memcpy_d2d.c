#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *host_update = (real_t *)malloc(2 * n * sizeof(real_t));;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        host_update[x] = 1;
        host_update[n + x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) create(hostdata[0:3*n]) copyout(c[0:n])
    {
        #pragma acc enter data create(host_update[0:2*n])
        acc_memcpy_d2d(hostdata, a, n * sizeof(real_t), acc_get_device_num(acc_get_device_type()), acc_get_device_num(acc_get_device_type()));
        acc_memcpy_d2d(&hostdata[n], b, n * sizeof(real_t), acc_get_device_num(acc_get_device_type()), acc_get_device_num(acc_get_device_type()));
        #pragma acc parallel present(hostdata[0:3*n], host_update[0:2*n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = hostdata[x] + hostdata[n + x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                hostdata[n + x] = 1.0;
            }
        }
        #pragma acc exit data copyout(host_update[0:2*n]) delete(hostdata[0:3*n])
        #pragma acc enter data copyin(host_update[0:2*n])
        acc_memcpy_d2d(c, hostdata, n * sizeof(real_t), acc_get_device_num(acc_get_device_type()), acc_get_device_num(acc_get_device_type()));
        #pragma acc parallel present(c[0:n], hostdata[0:3*n], host_update[0:2*n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                if (fabs(c[x] - (a[x] + b[x] + host_update[x]))) {
                    host_update[n + x] = 1;
                }
            }
        #pragma acc exit data copyout(host_update[0:2*n]) delete(hostdata[0:3*n])
        }
        for (int x = 0; x < n; ++x){
            if (fabs(host_update[x] - 1) > PRECISION){
                err += 1;
            }
            if (fabs(host_update[n + x] - 1) > PRECISION){
                err += 1;
            }
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