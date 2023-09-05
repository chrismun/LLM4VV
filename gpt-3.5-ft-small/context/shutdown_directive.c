#ifndef T1
//T1:shutdown,async,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int shutdown_test = 0;
    #pragma acc shutdown
    { shutdown_test = 1; }
    #pragma acc parallel
    {}

    if (shutdown_test != 1){
        return 1;
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