#ifndef T1
//T1:parallel,enter-data,exit-data,V:2.7-2.7
int test(){
    int err = 0;
    srand(4321);

    real_t * ahost = (real_t *)malloc(n * sizeof(real_t));
    real_t * bhost = (real_t *)malloc(n * sizeof(real_t));
    real_t * adevice = (real_t *)malloc(n * sizeof(real_t));
    real_t * bdevice = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        ahost[x] = rand() / (real_t)(RAND_MAX / 10);
        bhost[x] = rand() / (real_t)(RAND_MAX / 10);
        adevice[x] = 0.0;
        bdevice[x] = 0.0;
    }

    #pragma acc enter data copyin(adevice[0:n], bdevice[0:n])
    #pragma acc parallel present(adevice[0:n], bdevice[0:n])
    {
        // Perform computations on the device
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            adevice[x] += bdevice[x];
        }
    }
    #pragma acc exit data copyout(adevice[0:n])
    #pragma acc data copyout(bdevice[0:n])
    {
        // Copy data back to host
        #pragma acc parallel copyout(bdevice[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                bdevice[x] = adevice[x];
            }
        }

        // Validate data copied back to host
        for (int x = 0; x < n; ++x){
            if (fabs(bdevice[x] - ahost[x]) > PRECISION){
                err += 1;
                break;
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
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}