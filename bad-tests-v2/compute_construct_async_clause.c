#ifndef T1
//T1:async,compute,data,if,construct-independent-tiling,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data copyin(b[0:n])
    #pragma acc enter data create(c[0:n])

    for (int x = 0; x < n; ++x){
        a_copy[x] = a[x];
    }

    #pragma acc update device(a[0:n])
    #pragma acc data present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc compute async(1)
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * a[x];
            }
        #pragma acc compute async(2)
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                b[x] = b[x] * b[x];
            }
        #pragma acc compute async(1) wait(2)
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
    }
    #pragma acc wait
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a_copy[x] * a_copy[x])) > PRECISION){
            err += 1;
        }
        if (fabs(b[x] - (a_copy[x] * a_copy[x])) > PRECISION){
            err += 1;
        }
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n])

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