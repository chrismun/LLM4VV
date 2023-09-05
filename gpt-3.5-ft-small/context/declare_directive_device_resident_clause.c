#ifndef T1
//T1:declare,data,construct-independent,V:1.0-2.7
int test1(){
    int err = 0;
    unsigned int j, devNum, i;
    unsigned int **a = (unsigned int **)malloc(acc_get_num_devices((acc_device_t)acc_get_device_type()) * sizeof(unsigned int *));
    unsigned int **dev_a;
    #pragma acc enter data copyin(dev_a[0:devNum], dev_a[0:devNum][0:10])
    #pragma acc parallel present(a[0:devNum], dev_a[0:devNum], dev_a[0:devNum][0:10])
    {
        #pragma acc loop gang private(i)
        for (devNum = 0; devNum < acc_get_num_devices((acc_device_t)acc_get_device_type()); ++devNum){
            #pragma acc loop vector private(i)
            for (i = 0; i < 10; ++i){
                dev_a[devNum][i] = 9;
            }
        }
        #pragma acc loop worker
        for (j = 0; j < 2048; ++j){
            for (devNum = 0; devNum < acc_get_num_devices((acc_device_t)acc_get_device_type()); ++devNum){
                #pragma acc loop vector
                for (i = 0; i < 10; ++i){
                    a[devNum][i] += dev_a[devNum][i];
                }
            }
        }
    }
    for (devNum = 0; devNum < acc_get_num_devices((acc_device_t)acc_get_device_type()); ++devNum){
        for (unsigned int x = 0; x < 10; ++x){
            if (a[devNum][x] != 4096){
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