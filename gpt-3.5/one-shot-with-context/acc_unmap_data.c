#ifndef T1
//T1:runtime,data,data-region,r,h:7.1-7.4
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    #pragma acc enter data create(a[0:n])

    #pragma acc parallel present(a[0:n])
    {
        for (int x = 0; x < n; ++x){
            a[x] = x;
        }
    }

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc host_data use_device(a[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] *= 2;
            }
        }
    }

    #pragma acc update host(a[0:n])

    for (int x = 0; x < n; ++x){
        if (a[x] != x * 2){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n])

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