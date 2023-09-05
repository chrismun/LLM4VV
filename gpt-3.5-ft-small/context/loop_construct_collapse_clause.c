#ifndef T1
//T1:loop,collapse,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t)); 
    real_t *b = (real_t *)malloc(2 * m * n * sizeof(real_t));
    real_t *totals = (real_t *)malloc(m * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x)
    {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < m * n; ++x)
    {
        totals[x] = 0.0;
    }
    for (int x = 0; x < 2 * m * n; ++x)
    {
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    
    #pragma acc data copyin(a[0:10*n], b[0:2*m*n]) copy(totals[0:m*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int x = 0; x < m; ++x)
            {
                for (int y = 0; y < n; ++y)
                {
                    totals[x * n + y] = b[x * n + y * 2] + b[x * n + y * 2 + 1];
                    #pragma acc loop seq
                    for (int z = 0; z < 10; ++z)
                    {
                        totals[x * n + y] += a[z * n + y];
                    }
                    totals[x * n + y] *= 2;
                }
            }
        }
    }
    
    for (int x = 0; x < m; ++x)
    {
        for (int y = 0; y < n; ++y)
        {
            real_t temp = 0;
            for (int z = 0; z < 10; ++z)
            {
                temp += a[z * n + y];
            }
            if (fabs(totals[x * n + y] - 2 * (temp + b[x * n + y * 2] + b[x * n + y * 2 + 1])) > PRECISION)
            {
                err = 1;
                break;
            }
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,collapse,combined-constructs,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t)); 
    real_t *b = (real_t *)malloc(2 * m * n * sizeof(real_t)); 
    real_t *totals = (real_t *)malloc(m * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x)
    {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < m * n; ++x)
    {
        totals[x] = 0.0;
    }
    for (int x = 0; x < 2 * m * n; ++x)
    {
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:10*n], b[0:2*m*n]) copy(totals[0:m*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2) gang private(totals)
            for (int x = 0; x < m; ++x)
            {
                #pragma acc loop gang private(totals)
                for (int y = 0; y < n; ++y)
                {
                    totals[x * n + y] = b[x * n + y * 2] + b[x * n + y * 2 + 1];
                    #pragma acc loop seq
                    for (int z = 0; z < 10; ++z)
                    {
                        totals[x * n + y] += a[z * n + y];
                    }
                    totals[x * n + y] *= 2;
                }
            }
        }
    }
    
    
    for (int x = 0; x < m; ++x)
    {
        for (int y = 0; y < n; ++y)
        {
            real_t temp = 0;
            for (int z = 0; z < 10; ++z)
            {
                temp += a[z * n + y];
            }
            if (fabs(totals[x * n + y] - 2 * (temp + b[x * n + y * 2] + b[x * n + y * 2 + 1])) > PRECISION)
            {
                err = 1;
                break;
            }
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed = failed + test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed = failed + test2();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}