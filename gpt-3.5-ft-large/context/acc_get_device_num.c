#ifndef T1
//T1:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int device_num;

    device_num = acc_get_device_num(acc_device_nvidia);
    for (int x = 0; x < 10; ++x){
        #pragma acc data device(1)
        { 
        device_num = acc_get_device_num(acc_device_nvidia);
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int device_num;

    if (acc_get_device_type() == acc_device_none){
        return err;
    }

    device_num = acc_get_device_num(acc_get_device_type());
    for (int x = 0; x < 10; ++x){
        #pragma acc data device(acc_get_device_type())
        { 
        device_num = acc_get_device_num(acc_get_device_type());
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