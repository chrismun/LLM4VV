#ifndef T1
//T1:kernels,collapse
int test1(){
    int err = 0;
    int i, j, devNum;

    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t multiplyer;

    for (devNum = 0; devNum < 10; ++devNum){
        acc_set_device_num(devNum, acc_device_nvidia);
        #pragma acc data create(multiplyer) copyout(a[0:10*n]) copyin(b[0:10*n])
        {
            multiplyer = devNum + 1;
            #pragma acc kernels present(multiplyer)
            {
                for (i = 0; i < 10; ++i){
                    #pragma acc loop gang collapse(2)
                    for (j = 0; j < 10 * n; ++j){
                        a[i * n + j] = multiplyer;
                    }
                }
                #pragma acc loop seq
                for (j = 0; j < 10 * n; ++j){
                    a[j] = a[j] + b[j];
                }
            }
        }
    }

    for (devNum = 0; devNum < 10; ++devNum){
        acc_set_device_num(devNum, acc_device_nvidia);
        for (i = 0; i < 10; ++i){
            for (j = 0; j < n; ++j){
                if (fabs(a[i * n + j] - ((devNum + 1) + b[i * n + j])) > PRECISION){
                    err = 1;
                }
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