#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int x;
    int a[N], b[N];

    srand(SEED);

    #pragma acc data copyin(a,b)
    {
        #pragma acc kernels
        {
            for (x = 0; x < N; x++){
                a[x] = rand() % 100;
                b[x] = rand() % 100;
            }
        }

        #pragma acc parallel
        {
            for (x = 0; x < N; x++){
                a[x] = a[x] + b[x];
            }
        }
    }

    for (x = 0; x < N; x++){
        if (a[x] != (b[x] + b[x])){
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