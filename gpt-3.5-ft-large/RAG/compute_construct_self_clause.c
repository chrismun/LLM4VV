#ifndef T1
//T1:self,if,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t c = 0.0;
    int on_device = acc_is_present(a, n * sizeof(real_t));
    int on_device2 = acc_is_present(b, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])

    #pragma acc data present(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 0;
            }
        }
        #pragma acc parallel present(a[0:n]) if(on_device) // The if makes the device execute the region
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x];
            }
        }
        #pragma acc parallel present(a[0:n]) if(on_device2) if(0) // The if makes the compiler disregard the region, the self makes the device execute it
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += 10;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n]))

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