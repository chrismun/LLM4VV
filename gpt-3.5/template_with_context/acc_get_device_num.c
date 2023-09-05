#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int device_num = acc_get_device_num(acc_device_not_host);

    if (device_num < 0){
        err = 1;
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