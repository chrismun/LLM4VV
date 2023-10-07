#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int i, j;
    int data[N];

    srand(SEED);

    for (i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    #pragma acc parallel loop vector
    for (j = 0; j < N; j++) {
        data[j] = data[j] * 2;
    }

    for (i = 0; i < N; i++) {
        if (data[i] % 2 != 0) {
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