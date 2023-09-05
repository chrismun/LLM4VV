#ifndef T1
//T1:wait,async,V:1.0-2.7
int test1(){
    int err = 0;
    float* a = (float*)malloc(n * sizeof(float));
    float* b = (float*)malloc(n * sizeof(float));
    float* c = (float*)malloc(n * sizeof(float));

    srand(SEED);

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (float)(RAND_MAX / 10);
        b[i] = rand() / (float)(RAND_MAX / 10);
        c[i] = 0.0f;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels wait
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                c[i] = a[i] + b[i];
            }
        }
    }

    for (int i = 0; i < n; ++i){
        if (fabs(c[i] - (a[i] + b[i])) > PRECISION){
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
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}