#ifndef T1
//T1:declare,data,link,combined-constructs,V:2.7
int test1(){
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    int errors = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }

    acc_create_data_real(a, n);
    acc_copyin_data_real(a, n);

    #pragma acc declare link(a)
    {
        #pragma acc parallel num_gangs(1) vector_length(1)
        {
            a[5] += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n]) delete(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 1) > PRECISION){
            errors += 1;
        }
    }

    return errors;
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