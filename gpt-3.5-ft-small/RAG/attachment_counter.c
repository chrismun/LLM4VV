#ifndef T1
//T1:runtime,data,executable-data,loop,V:2.0-2.7
int test1(){
    int i, err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * d_a = (real_t *)malloc(n * sizeof(real_t));
    int found = 0;

    for (i = 0; i < n; ++i){
        a[i] = 1;
        d_a[i] = i;
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc parallel num_workers(1)
        {
            #pragma acc loop gang
            for (i = 0; i < n; ++i){
                #pragma acc atomic
                    a[i] = 2 * a[i];
            }
        }
    }

    for (i = 0; i < n; ++i){
        if (fabs(a[i] - 2) > PRECISION) {
            err += 1;
            break;
        }
    }

    #pragma acc data copyin(d_a[0:n])
    {
        found = 0;
        #pragma acc parallel num_workers(1)
        {
            #pragma acc loop gang
            for (i = 0; i < n; ++i){
                if (fabs(a[i] - d_a[i]) > PRECISION) {
                    found = 1;
                }
            }
        }
        if (found == 0){
            err++;
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