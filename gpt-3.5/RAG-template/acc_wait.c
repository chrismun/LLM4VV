#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Placeholder for testing acc_wait
    int async_queue = acc_async_test();
    acc_async_present(async_queue);

    // Testing acc_wait
    acc_wait(async_queue);

    // Check if acc_async_test completed successfully
    if(acc_async_test_check(async_queue)){
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