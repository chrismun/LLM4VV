#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int size = 100;
    int *A = (int*)malloc(size * sizeof(int));
    int *B = (int*)malloc(size * sizeof(int));

    // initialize A and B with random values
    for(int i = 0; i < size; i++){
        A[i] = rand() % size;
        B[i] = rand() % size;
    }

    // update B array in device memory with values from A array in local memory
    acc_update_device(B, size * sizeof(int));

    // check if B array in device memory has been correctly updated
    for(int i = 0; i < size; i++){
        if(B[i] != A[i]){
            err = 1;
            break;
        }
    }

    free(A);
    free(B);

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