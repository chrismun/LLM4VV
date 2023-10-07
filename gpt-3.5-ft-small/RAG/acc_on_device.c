#ifndef T1
//T1:runtime,data,executable-data,loop,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 1;
        c[x] = 3;
        d[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n], c[0:n]) create(b[0:n], d[0:n])
    for (int x = 0; x < n; ++x){
        a_copy[x] = a[x];
        b_copy[x] = b[x];
    }
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n], d[0:n], a_copy[0:n], b_copy[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 0;
            b[x] = 2;
        }
    }
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < a[x] + b[x]; ++y){
            a_copy[x] += c[x] * d[x];
        }
    }
    #pragma acc exit data delete(a[0:n]) copyout(a_copy[0:n]) delete(b[0:n]) copyout(b_copy[0:n])
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < a[x] + b[x]; ++y){
            if (fabs(a_copy[x] - (a[x] + c[x] * d[x])) > PRECISION) {
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