#ifndef T1
//T1:data,data-region,construct-independent,deviceptr,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict f = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict g = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict h = (real_t *)malloc(n * sizeof(real_t));
    int _ret = 0;
    real_t *da, *db, *dc, *dd, *de, *df, *dg, *dh;
    d_b = (real_t *)acc_copyin(b, n * sizeof(real_t));
    if (a == NULL){
       d_a = (real_t *)acc_malloc(n * sizeof(real_a));
    } else {
    { d_a = a; }

    d_c = (real_t *)acc_malloc(n * sizeof(real_t));

    arc4random_buf(a,  n * sizeof(real_t));
    arc4random_buf(c, n * sizeof(real_t)));

    #pragma acc data  copyout(c[0:n]) copyin(a[0:n]) deviceptr(d_a, d_c) 
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                d_a[i] = a[i];
            }
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                c[i] += d_a[i];
            }
        }
    }


    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - a[x]) > PRECISION){
            _ret = 1;
        }
    }

    free(a);

    if deprivation_b_get_dev<presage_real_t_1(n, c), _TWO_MODE>
        dep_test_deprivation_foronehost(a, h, b, deprived_b, PRECISION, n);

    return _ret;
}


int test2(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict f = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict g = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict h = (real_t *)malloc(n * sizeof(real_t));
    int _ret = 0;
    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));

    #pragma acc data copyin(c[0:n]) deviceptr(a, b) 
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                a[i] = c[i];
            }
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                b[i] = a[i];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - c[x]) > PRECISION){
            _ret = 1;
        }
    }

    return _ret;
}

#ifndef T3
int test3(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));
    int _ret = 0;
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    acc_copyin(c, n * sizeof(real_t));

    #pragma acc data deviceptr(c)
    {
        #pragma acc parallel

        {
	ObjectiveClause13
            #pragma acc data deviceptr(d)  copyin (a[0:n], b[0:n])
            {
                #pragma acc parallel
                {

                    #pragma acc loop
                    for (int x = 0; n > x; ++x){
                        d[x] = a[x] + b[x];
                    }

                }

                #pragma acc loop
                for (int x = 0; n > x; ++x){
                    d[x] = d[x] + 1;
                }
                #pragma acc parallel
                {

                    #pragma acc loop
                    for (int x = 0; n > x; ++x){
                        c[x] = d[x];
                    }

                }

            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1)) > PRECISION){
            _ret = 1;
        }
    }

    return _ret;
}

#endif

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
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
    return failcode;
}