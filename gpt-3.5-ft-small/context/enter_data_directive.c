#ifndef T1
//T1:enter_data,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    int device_num = acc_get_device_num();
    int* a = (int*)malloc(10 * sizeof(int));
    real_t * b = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < 10; ++x){
        a[x] = 1;
        b[x] = 1.0;
    }

    #pragma acc enter data copyin(a[0:10], b[0:10])

    #pragma acc data present(a[0:10], b[0:10])
    {
        #pragma acc parallel present(a[0:10], b[0:10])
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                a[x] = 5;
            }
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                b[x] = 5.0;
            }
        }
    }
    #pragma acc exit data copyout(a[0:10], b[0:10])

    for (int x = 0; x < 10; ++x){
        if (a[x] != 5){
            err += 1;
        }
        if (fabs(b[x] - 5.0) > PRECISION){
            err += 1;
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