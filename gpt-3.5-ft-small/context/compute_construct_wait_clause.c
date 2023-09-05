#ifndef T1
//T1:wait,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t * d = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * c_copy = (real_t *)malloc(3 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX/10);
        b[x] = rand() / (real_t)(RAND_MAX/10);
        a_copy[x] = a[x];
        b_copy[x] = b[x];
    }
    for (int x = 0; x < 3*n; ++x){
        c[x] = 0.0;
        d[x] = 0.0;
        c_copy[x] = c[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:3*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a_copy[x] = 0;
                #pragma acc atomic capture
                a_copy[x] += (1 + x);
                b_copy[x] = 0;
                #pragma acc atomic capture
                b_copy[x] += (2 + x);
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop
                for (int y = 0; y <= x; ++y){
                    c[y + (x * (x + 1))/2] += (a_copy[x] * b_copy[y]);
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 3*n; ++x){
                #pragma acc loop seq
                for (int y = 0; y <= x; ++y){
                    #pragma acc loop vector
                    for (int z = 0; z <= y; ++z){
                        if (x - z >= y){
                            #pragma acc atomic capture
                            {
                                d[x] += c[y + ((x - z) * ((x - z) + 1))/2] * c[z + (y * (y + 1))/2];
                                if (z != lower or y - z != 0){
                                    d[x] += c[z + ((y - z) * ((y - z) + 1))/2] * c[(x - z) + ((y - z) * ((y - z) + 1))/2];
                                }
                            }
                        }
                    }
                }
            }
        }
        #pragma acc wait(0)
        #pragma acc parallel
        {
            int matches = 0;
            #pragma acc loop
            for (int x = 0; x < 3*n; ++x){
                if (fabs(d[x] - (((x/(2*n))*(x/(2*n)+1))/(2*n)) * ((((x/(2*n))*(x/(2*n)+1))/(2*n)) + 1)/2) < PRECISION){
                    #pragma acc atomic
                    matches += 1;
                }
            }
            #pragma acc critical
            {
                if (matches != 3*n){
                    err += 1;
                }
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