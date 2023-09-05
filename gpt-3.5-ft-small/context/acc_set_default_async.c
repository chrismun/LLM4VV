#ifndef T1
//T1:runtime,async,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t sa, sb, async_undef;
    int i;

    for (i = 0; i < n; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = rand() / (real_t)(RAND_MAX / 10);
    }
    sa = sb = 0;
    async_undef = 1;
    acc_set_default_async(acc_async_noval);
    #pragma acc data present_or_copyin(a[0:n], b[0:n]) create(sa, sb)
    {
        #pragma acc serial
        {
            #pragma acc loop
            for (i = 0; i < n; ++i){
                #pragma acc atomic
                    sa = sa + a[i];
                #pragma acc atomic
                    sb = sb + b[i];
            }
        }

        #pragma acc kernel async // expected-warning {{expression has no effect}}
        {
            for (i = 0; i < n; ++i){
                #pragma acc atomic
                    sa = sa + a[i];
                #pragma acc atomic
                    sb = sb + b[i];
            }
        }
        #pragma acc parallel async (10) // expected-warning {{unexpected OpenACC directive '#pragma acc parallel'}}
        {
            #pragma acc loop
            for (i = 0; i < n; ++i){
                #pragma acc atomic
                    sa = sa + a[i];
                #pragma acc atomic
                    sb = sb + b[i];
            }
        }
        for (i = 0; i < n; ++i){
            #pragma acc atomic
                sa = sa + a[i];
            #pragma acc atomic
                sb = sb + b[i];
        }
        #pragma acc wait
        async_undef = 2;
    }
    if (async_undef == 1){
        for (i = 0; i < n; ++i){
            #pragma acc atomic
                sa = sa + a[i];
            #pragma acc atomic
                sb = sb + b[i];
        }
        async_undef = 2;
    }

    for (i = 0; i < n; ++i){
        #pragma acc atomic
            sa = sa + a[i];
        #pragma acc atomic
            sb = sb + b[i];
    }
    if (fabs((2 * sb - sa) / sa) > PRECISION){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,async,construct-independent,V:2.5-2.7
int test2(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t sa, async0, async1, async2, async3;
    async0 = acc_get_default_async();
    async1 = 1000;
    async2 = 50;
    async3 = async0;
    printf("%d\n", acc_get_default_async());
    acc_set_default_async(async1);
    printf("%d\n", acc_get_default_async());
    acc_set_default_async(async0);
    printf("%d\n", acc_get_default_async());
    int i;
    for (i = 0; i < n; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = rand() / (real_t)(RAND_MAX / 10);
    }
    sa = 0;
    async0 = 1;
    acc_set_default_async(async0);
    acc_set_default_async(async2);
    #pragma acc data present_or_copyin(a[0:n], b[0:n]) copyout(async0)
    {
        async0 = acc_get_default_async();
        #pragma acc parallel loop
        for (i = 0; i < n; ++i){
            #pragma acc atomic
                sa = sa + a[i];
        }
        #pragma acc parallel loop async(100) private(i)
        for (i = 0; i < n; ++i){
            b[i] = sa * b[i];
        }
    }
    async2 = acc_get_default_async();
    #pragma acc wait(100)
    #pragma acc data present_or_copyin(b[0:n]) copyout(async1)
    {
        async1 = acc_get_default_async();
    }
    if (async0 == async3){
        err = 1;
    }
    else if (async2 == async3){
        err = 1;
    }
    else if (async1 == async3){
        err = 1;
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