#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data;
    size_t bytes = sizeof(int) * SIZE;
    data = (int *)malloc(bytes);
    if(data == NULL){
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }

    #pragma acc enter data copyin(data[0:SIZE])
    #pragma acc parallel loop
    for(int i = 0; i < SIZE; i++){
        data[i] = i;
    }
    #pragma acc exit data delete(data[0:SIZE])

    if(!acc_is_present(data, bytes)){
        err = 1;
    }

    free(data);

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