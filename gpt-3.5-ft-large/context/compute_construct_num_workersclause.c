#ifndef T1
//T1:parallel,loop,combined-constructs,V:2.7-3.2,2.7-3.2,2.7-3.2
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * b = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * c = (real_t *)malloc(1024 * sizeof(real_t));

    for (int x = 0; x < 1024; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:1024], b[0:1024]) copyout(c[0:1024])
    {
        #pragma acc parallel num_workers(16)
        {
            #pragma acc loop
            for (int x = 0; x < 1024; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < 1024; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int called = 0;
    int total = 0;
    int failcode = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        called = 1;
        total++;
        failcode += test1();
    }
#endif
    return failcode;
}