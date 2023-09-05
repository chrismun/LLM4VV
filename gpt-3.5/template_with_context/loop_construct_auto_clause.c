#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc kernels loop auto
    for (int i = 0; i < 100; i++) {
        int k = i + 1;
        #pragma acc loop seq
        for (int j = 0; j < 10; j++) {
            k += j;
        }
        if (k != i + 56) {
            err = 1;
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