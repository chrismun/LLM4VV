#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop device_type(nvidia)
    for (int i = 0; i < SIZE; i++){
        arr[i] = i;
    }

    #pragma acc parallel loop device_type(radeon)
    for (int i = 0; i < SIZE; i++){
        arr[i] = i;
    }

    #pragma acc parallel loop device_type(any)
    for (int i = 0; i < SIZE; i++){
        arr[i] = i;
    }

    // Check if all elements of the array have been updated
    for (int i = 0; i < SIZE; i++){
        if (arr[i] != i){
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