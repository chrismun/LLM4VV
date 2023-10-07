#ifndef T1
//T1:compute,construct-independent,default-clause,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * m * sizeof(real_t));
    real_t *totals = (real_t *)malloc(n * sizeof(real_t));
    real_t temp = 0.0;

    for (int x = 0; x < n; ++x){
        totals[x] = 0;
        for (int y = 0; y < m; ++y){
            a[x * m + y] = rand() / (1.0 + RAND_MAX);
            totals[x] += a[x * m + y];
        }
    }

    #pragma acc data copyin(a[0:n*m]) copy(totals[0:n])
    {
        #pragma acc compute default(present)
        for (int x = 0; x < n; ++x){
            temp = 0;
            for (int y = 0; y < m; ++y){
                temp += a[x * m + y];
            }
            #pragma acc loop
            for (int y = 0; y < m; ++y){
                b[x * m + y] = a[x * m + y] / temp * totals[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        temp = 0.0;
        for (int y = 0; y < m; ++y){
            temp += b[x * m + y];
        }
        for (int y = 0; y < m; ++y){
            if (fabs(b[x * m + y] - a[x * m + y] / totals[x] * totals[x]) < PRECISION * temp){
                err += 1;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}