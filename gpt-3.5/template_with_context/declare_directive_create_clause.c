#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare variables
    int *a = (int*) malloc(N * sizeof(int));
    int *b = (int*) malloc(N * sizeof(int));
    int *c = (int*) malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Create data region
    #pragma acc data create(a[0:N], b[0:N], c[0:N])
    {
        // Perform computation
        #pragma acc parallel loop present(a[0:N], b[0:N], c[0:N])
        for (int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }

    // Verify results
    for (int i = 0; i < N; i++){
        if (c[i] != a[i] + b[i]){
            err = 1;
        }
    }

    // Cleanup
    free(a);
    free(b);
    free(c);

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