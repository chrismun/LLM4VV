#ifndef T1
//T1:runtime,data,data-region,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int* a = (int *)malloc(n * sizeof(int));
    real_t * dev = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = x;
        dev[x] = (((unsigned)x) / n) * 10;
    }

    #pragma acc data \
        copyin(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                real_t b = dev[x];
                #pragma acc atomic
                dev[x] = b + a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(dev[x] - (10 + ((real_t) x))) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,data-region,construct-independent,reference-pointers,V:2.0-2.7
int test2(){
    int err = 0;
    int * c = (int *)malloc(n * sizeof(int));
    int * d = (int *)malloc(n * sizeof(int));
    real_t * dev1 = (real_t *)acc_malloc(n * sizeof(real_t));
    int * dev2 = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        c[x] = 1;
        d[x] = 0;
        dev1[x] = 0;
        dev2[x] = x;
    }

    #pragma acc data copy(dev1[0:n]) copyin(dev2[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev1[x] = dev2[x] + c[x];
                d[x] = c[x] + 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(dev1[x] - (1 + ((real_t) x))) > PRECISION){
            err += 1;
        }
        if (fabs(((real_t) d[x]) - (1 + ((real_t) c[x]))) > PRECISION){
            err += 1;
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