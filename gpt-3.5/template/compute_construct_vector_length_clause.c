#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    float a[n], b[n], c[n];

    // Initialize arrays
    for (int i = 0; i < n; i++){
        a[i] = (float)(i+1);
        b[i] = (float)(i+2);
        c[i] = 0.0f;
    }

    // Compute c = a + b using OpenACC compute construct and vector_length clause
    #pragma acc kernels loop vector_length(4)
    for (int i = 0; i < n; i++){
        c[i] = a[i] + b[i];
    }

    // Verify the results
    for (int i = 0; i < n; i++){
        if (c[i] != a[i] + b[i]){
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