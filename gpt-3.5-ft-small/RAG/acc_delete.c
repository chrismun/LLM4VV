#ifndef T1
//T1:runtime,data,executable-data,construct-independent,acc7.1,print-outside-data,delete,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    n = 1;
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));

    real_t false_margin = ERR_MARGIN;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 1;
        c[x] = 0;
    }

    #pragma acc enter data create(a[0:n], b[0:n])
    #pragma acc parallel present(a[0:n], b[0:n]) create(c[0:n])
    {
    #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2) > false_margin){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,acc7.1,print-outside-data,delete,async,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    n = 1;
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));
    int * d = (int *)malloc(n * sizeof(int));

    real_t false_margin = ERR_MARGIN;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 1;
        c[x] = 0;
        d[x] = 0;
    }

    #pragma acc enter data create(a[0:n], b[0:n])
    #pragma acc parallel present(a[0:n], b[0:n]) create(c[0:n]) async(1)
    {
    #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc parallel present(c[0:n]) create(d[0:n]) async(1)
    {
    #pragma acc loop
        for (int x = 0; x < n; ++x){
            d[x] = c[x];
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) async(1)
    #pragma acc wait(1)
    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - 2) > false_margin){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}