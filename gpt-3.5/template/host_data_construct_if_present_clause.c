#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data;
    int present = 1;

    #pragma acc enter data create(data) if(present)
    #pragma acc exit data copyout(data) if_present(present)

    if(present){
        int sum = 0;
        for(int i = 0; i < N; i++){
            data[i] = rand() % 10;
            sum += data[i];
        }

        if(sum != N*9/2){
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