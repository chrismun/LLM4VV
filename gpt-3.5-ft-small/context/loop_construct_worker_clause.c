#ifndef T1
//T1:loop,construct-independent,V:1.0-2.7
int test1(){
    int err = 0;
    int i;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t temp = 0.0;

    for (i = 0; i < n; ++i){
            a[i] = 1;
            b[i] = 1;
            c[i] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    {
        #pragma acc parallel num_gangs(1) num_workers(256) vector_length(32) present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop gang worker vector
            for (int x = 0; x < n; ++x){
                c[x] = 0;
            }
            #pragma acc loop worker
            for (int x = 0; x < n; ++x){
                #pragma acc loop seq
                for (int y = 0; y < n; ++y){
                    c[x] += a[x] * b[y];
                }
            }
        }
    }

    for (i = 0; i < n; ++i){
            temp += a[i] + b[i];
    }
    temp = temp * (temp/2 + 1);

    for (i = 0; i < n; ++i){
            temp -= c[i];
    }
    free(a);
    free(b);
    free(c);
    if (fabs(temp) - (n + 1) * n / 2 > PRECISION){
            err += 1;
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