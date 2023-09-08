#ifndef T1
//T1:reduction,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t reduction;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    #pragma acc data copyin(a[0:n])
    {
      for (int x = 0; x < n; ++x){
    #pragma acc parallel loop reduction(+:reduction)
        for (int y = 0; y < n; ++y){
            reduction = a[y] * .5;
        }
        if (fabs(reduction - (a[x] * .5)) > PRECISION){
            err = 1;
        }
      }
    }

    return err;
}
#endif

#ifndef T2
//T2:reduction,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int ** a = (int **)malloc(n * sizeof(int *));
    int * adata = (int *)malloc(n * n * sizeof(int));
    int * prod = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            a[x][y] = rand() / (int)(RAND_MAX / 10);
        }
    }

    for (int x = 0; x < n; ++x){
        prod[x] = 1;
    }

    #pragma acc data copyin(a[0:n][0:n], prod[0:n])
    {
        #pragma acc parallel loop reduction(*:prod)
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < n; ++y){
                prod[x] += a[x][y];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for(int  y = 0; y < n; ++y){
            adata[x * n + y] = a[x][y];
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            prod[x] -= a[x][y];
        }
    }

    for (int x = 0; x < n; ++x){
        if (prod[x] != 0){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:reduction,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    _Bool result = 1;
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 2;
        b[x] = 3;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop reduction(&:result)
        for (int x = 0; x < n; ++x){
            result = result && c[x];
            for (int y = 0; y < b[x]; ++y){
                c[x] += a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (!c[x]){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:reduction,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 2;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop reduction(+:b[0:n])
        for (int x = 0; x < n; ++x){
            b[x] += a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != 2 * a[x]){
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