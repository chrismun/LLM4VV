#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int check = 0;
    int n = 1000;
    int x[n], y[n];

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        x[i] = i;
        y[i] = 0;
    }

    #pragma acc kernels loop auto
    for (int i = 0; i < n; ++i) {
        y[i] = x[i] * 2;
    }

    // Verify results
    for (int i = 0; i < n; ++i) {
        if (y[i] != x[i] * 2) {
            check = 1;
            break;
        }
    }

    if (check) {
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