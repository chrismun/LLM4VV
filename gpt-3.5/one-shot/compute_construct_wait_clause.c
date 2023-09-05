#ifndef T1
//T1:wait,async,V:1.0-2.7
int test1(){
    int err = 0;

    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));
    real_t* c = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = x * 1.0;
        b[x] = x * 2.0;
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop gang async
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }

        #pragma acc wait

        #pragma acc parallel loop gang async
        for (int x = 0; x < n; ++x){
            c[x] += 1.0;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1.0)) > PRECISION){
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