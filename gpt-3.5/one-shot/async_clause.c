#ifndef T1
//T1:parallel,data,data-region,async,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    // Create an async handle
    acc_async_handle_t async_handle;

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel copyout(b[0:n])
        {
            // Assign the async handle to a value
            async_handle = acc_async_noval;

            #pragma acc loop async(async_handle)
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Wait for the completion of the async region
    acc_wait_all(async_handle);

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