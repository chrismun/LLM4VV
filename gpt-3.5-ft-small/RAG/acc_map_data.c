#ifndef T1
//T1:routine,construct-independent,executable-data-mapping-mapping-assert-1
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t *e = (real_t *)malloc(n * sizeof(real_t));
    real_t *f = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 0;
        e[x] = a[x];
        f[x] = b[x];
	a_copy[x] = a[x];
    }
    real_t * a_remap = a;
    
    #pragma acc data copyin(a_remap[0:n:1], c[0:n:1]) copyout(d[0:n:1])
    {
        #pragma acc parallel present(a_remap[0:n:1], c[0:n:1], d[0:n:1])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = 3;
                d[x] = 0;
            }
        }
        acc_map_data(a_remap, d, n * sizeof(real_t));
    }
    
    for (int x = 0; x < n; ++x){
        if (fabs(a_remap[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
        if (fabs(c[x] - 3.0) > PRECISION){
            err += 1;
        }
        if (fabs(d[x] - 3.0) > PRECISION){
            err += 1;
        }
    }
    
    return err;
}
#endif

#ifndef T2
//T2:routine,construct-independent,executable-data-mapping-mapping-assert-2
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t *e = (real_t *)malloc(n * sizeof(real_t));
    real_t *f = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 0;
        e[x] = a[x];
        f[x] = b[x];
	a_copy[x] = a[x];
    }
    real_t * a_remap = a;
    
    #pragma acc data copyin(a_remap[0:n:1], c[0:n:1]) copyout(d[0:n:1])
    {
        #pragma acc parallel present(a_remap[0:n:1], c[0:n:1], d[0:n:1])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = 3;
                d[x] = 0;
            }
        }
        acc_map_data(a_remap, d, n * sizeof(real_t));
	#pragma acc parallel present(a_remap[0:n:1], d[0:n:1])
	{
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a_remap[x];
            }
        }
    }
    
    for (int x = 0; x < n; ++x){
        if (fabs(a_remap[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
	if (fabs(d[x] - a_copy[x]) > PRECISION){
            err += 1;
	}
        if (fabs(c[x] - 3.0) > PRECISION){
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