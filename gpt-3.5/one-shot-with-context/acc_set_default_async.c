#ifndef T2
//T2:parallel,async,async-default,set-default,devicedevice:data,data-region,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int default_async_copy_device_a;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc set_default_async(0)
        {
            #pragma acc parallel async(1)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] = a[x];
                }
            }

            #pragma acc parallel async(2)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] += a[x];
                }
            }
            
            #pragma acc wait_async(2)
        }
    }

    #pragma acc exit data copyout(default_async_copy_device_a)
    err += (default_async_copy_device_a != acc_async_default);

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
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