#ifndef T1
//T1:construct-independent,possible-advise,devonly,devonly-signedint,loop,V:2.0-22
int test1(){
    int err = 0;
    int device_type;

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:2*n])
    {
        #pragma acc parallel loop gang device_type(ACC_DEVICE_NVIDIA) vector_present(device_type)
        for (int x = 0; x < n; ++x){
            #pragma acc loop vector device_type(ACC_DEVICE_NVIDIA) gang
            for (int y = 0; y < 2; ++y){
                device_type = acc_get_device_type();
                c[x + y] = (device_type == acc_device_nvidia) ? (a[x] + b[x]) : 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
        if (fabs(c[n + x] - 1) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:construct-independent,possible-advise,devonly,devonly-signedint,loop,V:2.0-22
int test2(){
    int err = 0;
    int device_type;

    real_t * a = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < 2*n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    acc_copyin(a, 2 * n * sizeof(real_t));
    acc_copyin(b, 2 * n * sizeof(real_t));

    #pragma acc parallel gang device_type(ACC_DEVICE_HOST) vector_present(device_type)
    {
        #pragma acc loop seq
        for (int x = 0; x < 2*n; ++x){
            c[x] = (a[x] + b[x]);
        }
    }

    #pragma acc data copyin(c[0:2*n])
    {
        #pragma acc parallel loop gang device_type(ACC_DEVICE_HOST) vector_present(device_type)
        for (int x = 0; x < 2*n; ++x){
            device_type = acc_get_device_type();
            if (fabs(c[x] - (a[x] + b[x])) > PRECISION && device_type == acc_device_host){
                err += 1;
            }
            else if (fabs(c[x] - a[x]) > PRECISION && device_type != acc_device_host){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}