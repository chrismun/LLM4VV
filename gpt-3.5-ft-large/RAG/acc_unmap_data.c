#ifndef T1
//T1:runtime,data,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * c_host = (real_t *)malloc(n * sizeof(real_t));
    int i;

    for (i = 0; i < n; ++i){
        a[i] = 0;
        a_host[i] = 0;
        b[i] = 0;
        b_host[i] = 0;
        c[i] = 0;
        c_host[i] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])

    for (int x = 0; x < 10; ++x){
        for (i = 0; i < n; ++i){
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc update device(a[0:n], b[0:n])

        #pragma acc data present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < (int) n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
            #pragma acc update host(c[0:n])
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x])) > 2*PRECI){
                c_host[x] = 1;
            }
        }

        #pragma acc unmap data(c[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(c_host[x] - c[x]) > PRECI){
                err += 1;
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