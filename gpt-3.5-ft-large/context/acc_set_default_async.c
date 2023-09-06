#ifndef T1
//T1:runtime,internal-control-values,syntactic,V:2.5-2.7
int test1(){
    int err = 0;

    if (acc_get_default_async() == acc_get_default_async()){
        acc_init_test(acc_get_device_type());
        if (acc_get_device_type() == acc_device_none){
            acc_set_default_async(acc_async_default);
            if (acc_get_default_async() != acc_async_none){
                err += 1;
            }
        }
        else{
            acc_set_default_async(1);
            if (acc_get_default_async() != 1){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,async,construct-independent,syntactic,YES,V:2.5-2.7
int test2(){
    int async = acc_get_default_async();
    int err = 0;

    #pragma acc set default_async(3)

    if (acc_get_default_async() != 3){
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