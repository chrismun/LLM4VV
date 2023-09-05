#ifndef T1

int test1(){
    int err = 0;

    #pragma acc enter data create(a[0:10])
    #pragma acc attach(a[0:2])

    for (int i = 0; i < 2; i++)
        a[i] = i;

    #pragma acc exit data delete(a[0:2])
    #pragma acc exit data copyout(a[0:10])

    for (int i = 0; i < 10; i++){
        if (a[i] != i){
            err++;
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