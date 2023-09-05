#ifndef T1
//T1:parallel,kernels,construct,V:2.7
int test1(){
    int err = 0;

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1.0;
        b[x] = 0.0;
    }

    #pragma acc kernels copyout(b[0:n])
    {
        #pragma acc loop independent
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != a[x]){
            err += 1;
            break;
        }
    }

    return err;
}

//T2:parallel,kernels,construct,V:2.7
int test2(){
    int err = 0;

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1.0;
        b[x] = 2.0;
        c[x] = 0.0;
    }

    #pragma acc kernels copyout(c[0:n]) copyin(a[0:n],b[0:n])
    {
        #pragma acc loop independent
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != a[x] + b[x]){
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

    return failcode;
}