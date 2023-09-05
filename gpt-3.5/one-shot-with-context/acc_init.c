#ifndef T1
//T1:parallel,loop,V:1.7-2.7
int test1(){
    int err = 0;

    acc_init(acc_device_default);

    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < 100; ++x){
            // Some computation
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