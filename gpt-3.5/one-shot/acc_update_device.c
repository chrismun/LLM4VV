#ifndef T1
//T1:parallel,update,data,runtime,V:2.0-2.7
int test1(){
    int err = 0;

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        c[x] = 0.0;
    }

    #pragma acc parallel loop
    for (int x = 0; x < n; ++x){
        c[x] = 2 * b[x];
    }

    #pragma acc update device(a[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = c[x];
    }

    #pragma acc update self(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - c[x]) > PRECISION){
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