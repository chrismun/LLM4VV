#ifndef T1
//T1:parallel,data,data-region,V:2.7
int test1(){
    int err = 0;
    int dev_type;

    #pragma acc set device_type(acc_device_nvidia)
    dev_type = acc_get_device_type();

    if (dev_type != acc_device_nvidia){
        err += 1;
    }

    return err;
}

//T2:parallel,data,data-region,V:2.7
int test2(){
    int err = 0;
    int dev_type;

    #pragma acc set device_type(acc_device_host)
    dev_type = acc_get_device_type();

    if (dev_type != acc_device_host){
        err += 1;
    }

    return err;
}

//T3:parallel,data,data-region,V:2.7
int test3(){
    int err = 0;
    int dev_type;

    #pragma acc set device_type((acc_device_t)3)
    dev_type = acc_get_device_type();

    if (dev_type != (acc_device_t)3){
        err += 1;
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
        failed = failed + test2();
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}