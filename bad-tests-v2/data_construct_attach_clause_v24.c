#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int array[10];

    #pragma acc data copyin(array[0:10]) attach(array)
    {
        // Access array
        for (int i = 0; i < 10; i++) {
            array[i] = i;
        }
    }
    
    // Verify array values
    for (int i = 0; i < 10; i++) {
        if (array[i] != i) {
            err = 1;
            break;
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