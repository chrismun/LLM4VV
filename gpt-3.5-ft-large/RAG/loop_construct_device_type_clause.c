#ifndef T1
//T1:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t total;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    total = 0.0;
    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(host) reduction(+:total)
    for (int x = 0; x < n; ++x){
        total += a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        total - (a[x] + b[x]);
    }

    return err;
}
#endif

#ifndef T2
//T2:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test2(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t total;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    total = 0.0;
    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(accelerator) reduction(+:total)
    for (int x = 0; x < n; ++x){
        total += a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        total - (a[x] + b[x]);
    }

    return err;
}
#endif

#ifndef T3
//T3:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test3(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t total;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    total = 0.0;
    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(host) reduction(+:total)
    for (int x = 0; x < n; ++x){
        total += a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        total - (a[x] + b[x]);
    }

    return err;
}
#endif

#ifndef T4
//T4:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test4(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t total;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    total = 0.0;
    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(accelerator) reduction(+:total)
    for (int x = 0; x < n; ++x){
        total += a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        total - (a[x] + b[x]);
    }

    return err;
}
#endif

#ifndef T5
//T5:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test5(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(host) 
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + b[x];
    }

    return err;
}
#endif

#ifndef T6
//T6:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test6(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(accelerator)
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + b[x];
    }

    return err;
}
#endif
#ifndef T7
//T7:construct-independent,device-type-independent,DRD,VDEV:2.6-2.7,2.8-3.2
int test7(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(host)
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + b[x];   
    }

    return err;
}
#endif

#ifndef T8
//T8:construct-independent,device-type-independent,DRD,V:2.6-2.7,2.8-3.2
int test8(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    #pragma acc loop device_type(accelerator)
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + b[x];   
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
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
#ifndef T6
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test6();
    }
    if (failed != 0){
        failcode = failcode + (1 << 5);
    }
#endif
#ifndef T7
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test7();
    }
    if (failed != 0){
        failcode = failcode + (1 << 6);
    }
#endif
#ifndef T8
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test8();
    }
    if (failed != 0){
        failcode = failcode + (1 << 7);
    }
#endif
    return failcode;
}