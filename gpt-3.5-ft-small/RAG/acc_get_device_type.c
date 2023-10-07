#ifndef T1
//T1:runtime,construct-independent,netconstruct-independent,V:2.7-2.7
int test1(){
    int err = 0;
    #pragma acc enter data create(a)
    acc_device_t dev_t = acc_get_device_type();
    if (dev_t != acc_get_device_type()){
        acc_update_device(&dev_t, 1);
        #pragma acc parallel
        {
            acc_device_t dev_id = acc_get_device_type();
            if (dev_id != dev_t){
                #pragma acc atomic write
                    err += 1;
            }
        }
    }
    #pragma acc exit data delete(a)

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