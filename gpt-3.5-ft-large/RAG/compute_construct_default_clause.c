#ifndef T1
//T1:compute,data,data-region,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 1;
    }

    #pragma acc data copyin(c[0:n]) copy(a[0:n]) copyout(b[0:n]) copy(d[0:n])
    {
        #pragma acc compute copy(a[0:n]) copyin(d[0:n]) default(present_or_copy) // Reference behavior
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = c[x] * d[x];
            }
        }
        #pragma acc compute copy(b[0:n]) copyin(d[0:n] default(present_or_copy)) // Same as above
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = c[x] * d[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:compute,data,data-region,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

    int dev = 0;
    _Bool  *devtest = acc_get_device_type();
    if (devtest[1]){
        dev = 1;
    }
    int * isDevice = (int *) malloc(sizeof(int));
    int init = 1;
    #pragma acc enter data copyin(isDevice[0:1])
    #pragma acc present(isDevice[0:1])
    isDevice[0] = init;
    #pragma acc update isDevice[0:1]
    if (isDevice[0] == init){
        dev = !dev;
    }
    #pragma acc exit data delete(isDevice)

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
    }

    acc_set_device_num(dev, 0);
    #pragma acc data copyin(c[0:n]) copyout(a[0:n]) copyout(b[0:n])
    {
        #pragma acc data copy(a[0:n]) create(c[0:n])
        {
            #pragma acc compute copyout(c[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = 1;
                }
            }
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = c[x] * a[x];
                }
            }
        }
        #pragma acc data copy(a[0:n]) create(c[0:n])
        {
            #pragma acc compute copyout(c[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = 1;
                }
            }
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = c[x] * a[x];
                }
            }
        }
        #pragma acc data copyin(a[0:n]) copy(c[0:n])
        {
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = c[x] * a[x];
                }
            }
            #pragma acc compute
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += 1;
                }
            }
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = c[x] * a[x];
                }
            }
        }
        #pragma acc data copyin(a[0:n]) copy(c[0:n])
        {
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = c[x] * a[x];
                }
            }
            #pragma acc compute worker
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += 1;
                }
            }
            #pragma acc compute copyin(c[0:n]) copy(a[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = c[x] * a[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (3. * PRE_LOOP_VAL)) > PRECISION * PRE_LOOP_VAL){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:compute,data,data-region,devonly,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

    int * is_present = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc compute create(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = 1;
            }
            #pragma acc data copyin(b[0:n]) copy(c[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + a[x]))) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:compute,data,data-region,devonly,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

    int * is_present = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc compute create(is_present[0:1], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = 1;
            }
            is_present[0] = 1;
        }
        #pragma acc data present(is_present[0:1]) copyin(b[0:n]) copy(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + a[x]))) > PRECISION){
            err += 1;
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
    return failcode;
}