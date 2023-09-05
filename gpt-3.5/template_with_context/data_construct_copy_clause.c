#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *arr = (int*) malloc(sizeof(int) * N);
    int *copy_arr = (int*) malloc(sizeof(int) * N);

    #pragma acc data copy(arr[0:N], copy_arr[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            arr[i] = rand() % 100;
            copy_arr[i] = arr[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (arr[i] != copy_arr[i]) {
            err = 1;
        }
    }

    free(arr);
    free(copy_arr);

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