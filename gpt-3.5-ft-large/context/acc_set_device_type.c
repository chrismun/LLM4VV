#ifndef T1
//T1:runtime,internal-control-values,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    acc_device_t device_type = acc_get_device_type();

    for (int x = 0; x < device_type_result_length; ++x){
        acc_set_device_type(device_type_result[x]);
        if (acc_get_device_type() != device_type_result[x]){
            err += 1;
        }
    }
    acc_set_device_type(device_type);

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