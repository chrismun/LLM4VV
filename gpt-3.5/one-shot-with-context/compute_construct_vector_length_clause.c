#ifndef T1
//T1:parallel,data,data-region,V:1.0-3.0
int test1(){
    int err = 0;
    
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = 0.0;
    }
    
    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copyout(d[0:n])
    {
        #pragma acc parallel vector_length(2512)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x] * c[x];
            }
        }
    }
    
    for (int x = 0; x < n; ++x){
        if(fabs(d[x] - (a[x] + b[x] * c[x])) > PRECISION){
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

    return failcode;
}