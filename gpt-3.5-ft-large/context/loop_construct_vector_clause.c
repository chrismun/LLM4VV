#ifndef T1
//T1:loop,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t multiplyer = 1;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t) RAND_MAX;
        b[x] = rand() / (real_t) RAND_MAX;
        c[x] = 0.0;
    }

  #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
  {
    #pragma acc parallel
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
        	c[x] = (a[x] + b[x]) * multiplyer;
        }
        multiplyer += 1;
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            c[x] += (a[x] + b[x]) * multiplyer;
        }
    }
  }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 3) > PRECISION * (a[x] + b[x])){
            err + = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,V:2.7-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t multiplyer[10];

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t) RAND_MAX;
        b[x] = rand() / (real_t) RAND_MAX;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n])
    {
        #pragma acc parallel 
        {
            #pragma acc loop vector length(10)
            for (int x = 0; x < 10 * n; ++x){
                c[x] = (a[x] + b[x]);
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) {
            err + = 1;
        }
    }

    return err;
}
#endif

#ifdef T3
//T3:
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * d = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * e = (real_t *)malloc(25 * n * sizeof(real_t));
    int dev = acc_get_device_type(a);

    for (int x = 0; x < 25 * n; ++x){
        a[x] = 1.5;
        b[x] = 2.5;
        c[x] = 3.5;
        d[x] = 4.5;
        e[x] = 5.5;
    }

    #pragma acc data copy(a[0:25*n], b[0:25*n], c[0:25*n], d[0:25*n], e[0:25*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop vector gang worker
            for (int x = 0; x < 25 * n; ++x){
                a[x] = a[x] + b[x];
            }
            #pragma acc loop vector gang worker
            for (int x = 0; x < 25 * n; ++x){
                c[x] = c[x] + d[x];
            }
            #pragma acc loop vector gang worker
            for (int x = 0; x < 25 * n; ++x){
                e[x] = e[x] + (a[x] + c[x]);
            }
        }
    }

    for (int x = 0; x < 25 * n; ++x){
        if (fabs(a[x] - (1.5 + 2.5)) > PRECISION){
            err + = 1;
        }
        if (fabs(c[x] - (3.5 + 4.5)) > PRECISION){
            err + = 1;
        }
        if (fabs(e[x] - (5.5 + (1.5 + 2.5) + (3.5 + 4.5))) > PRECISION * 4){
            err + = 1;
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
    return failcode;
}