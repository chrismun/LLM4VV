#ifndef T1
//T1:declare,data,executable,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * hasDevice = (int *)malloc(sizeof(int));
    hasDevice[0] = 1;
    real_t false_margin = pow(exp(1), log(.5)/n);

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
    }

    #pragma acc enter data create(a[0:n], b[0:n])

	#pragma acc declare device_resident(hasDevice)
    #pragma acc parallel present(a[0:n], b[0:n], hasDevice[0:1])
    {
        hasDevice[0] = 1;
    }

    #pragma acc update host(hasDevice[0:1])

    if (hasDevice[0] == 0){
        for (int x = 0; x < n; ++x){
            a[x] = 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (hasDevice[0] == 1){
            if (a[x] != 0){
                err += 1;
            }
        }
        else {
            if (a[x] != 1){
                err += 1;
            }
        }
        if (b[x] != 0){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n])
    #pragma acc exit data delete(a[0:n], b[0:n])

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