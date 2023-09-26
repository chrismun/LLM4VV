#ifndef T1
//T1:runtime,async,construct-independent,wait,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t *e = (real_t *)malloc(n * sizeof(real_t));
    real_t *f = (real_t *)malloc(n * sizeof(real_t));
    real_t *g = (real_t *)malloc(n * sizeof(real_t));
    real_t *h = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
        g[x] = 0.0;
        h[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n]) copy(c[0:n], f[0:n], g[0:n], h[0:n])
    {
        #pragma acc enter data create(h[0:n])
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        acc_detach(c, n * sizeof(real_t));
        #pragma acc parallel present(c[0:n], h[0:n]) async(2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                h[x] = c[x] * c[x];
            }
        }
        #pragma acc enter data create(g[0:n])
        #pragma acc parallel present(d[0:n], e[0:n], g[0:n]) async(3)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                g[x] = d[x] + e[x];
            }
        }
        acc_detach(g, n * sizeof(real_t));

        #pragma acc parallel present(c[0:n], g[0:n], h[0:n]) async(4)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += g[x] + h[x];
            }
        }

        #pragma acc enter data copyout(c[0:n]) 
        #pragma acc parallel present(c[0:n]) async(4)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += 1;
            }
        }
        #pragma acc wait(1, 2, 3, 4)
    }
 
    real_t cVal;
    for (int x = 0; x < n; ++x){
        cVal = a[x] + b[x] + ((a[x] + b[x]) * (a[x] + b[x])) + 1;
        if(fabs(c[x] - cVal) > PRECISION){
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
    for (int x = 0; x < NUM_TEST; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}