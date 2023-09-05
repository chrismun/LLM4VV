#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a[10];
    int b[10];
    int c[10];

    #pragma acc data copyin(a,b) copyout(c)
    {
        #pragma acc kernels loop device_type(nvidia)
        for(int i = 0; i < 10; i++){
            c[i] = a[i] + b[i];
        }
    }

    for(int i = 0; i < 10; i++){
        if(c[i] != a[i] + b[i]){
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