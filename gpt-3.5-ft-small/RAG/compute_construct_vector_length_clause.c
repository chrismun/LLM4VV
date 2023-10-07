#ifndef T1
//T1:parallel,loop,VLENGTH,VLENGTH-nested,reduction,combined-constructs,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc((n/10 + 1) * 10 * sizeof(real_t));
    int *num_c = (int *)malloc(1 * sizeof(int));
    real_t *totals = (real_t *)malloc((n/10 + 1) * 10 * sizeof(real_t));
    int passed;
    int device_type = acc_get_device_type();
#ifdef HOST_DATA_DEFAULT_PRESENT
    if (device_type == acc_device_host) {
        for (unsigned int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }
    }
#endif
    for (int x = 0; x < n/10 + 1; ++x){
        totals[x] = -1;
    }
    for (int x = 0; x < n/10 + 1; ++x){
        num_c[0] = 0;
#pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n/10 + 1]) copy(num_c[0:1]) copyout(totals[0:n/10 + 1])
        {
#ifndef T4
#pragma acc parallel
#endif
            {
                real_t my_total;
                int my_num = 0;
#ifdef T4
#pragma acc loop
#else
#pragma acc loop gang vector_length(AS)
#endif
                for (unsigned int x = 0; x < n; ++x){
                    my_total = 0;
#ifdef T4
#pragma acc loop reduction(+:my_total)
#else
#pragma acc loop worker vector reduction(+:my_total)
#endif
                    for (unsigned int y = 0; y < 8; ++y){
                        my_total += (a[x] + b[x]) / 2;
                    }
                    if (fabs(my_total - c[x/10]) < PRECISION){
                        my_num += 1;
                    }
                }
                totals[x/10] = my_total;
                num_c[0] += my_num;
            }
        }
    }
    for (int x = 0; x < n/10 + 1; ++x){
        if (fabs(totals[x] - c[x]) > n * PRECISION){
            passed = 0;
        }
    }
    if (fabs(num_c[0] - (n/10 + 1)) > (real_t) (n * PRECISION)){
        passed = 0;
    }
#ifdef HOST_DATA_DEFAULT_PRESENT
    if (device_type == acc_device_host) {
        for (unsigned int x = 0; x < n; ++x){
            a[x] = -1;
            b[x] = -1;
        }
        for (unsigned int x = 0; x < n / 10 + 1; ++x){
            c[x] = -1;
        }
        for (unsigned int x = 0; x < n / 10 + 1; ++x){
            totals[x] = -1;
        }
        for (unsigned int x = 0; x < 1; ++x){
            num_c[x] = -1;
        }
        for (unsigned int x = 0; x < n / 10 + 1; ++x){
            for (unsigned int y = 0; y < 8; ++y){
                totals[x] = 0;
            }
        }
        return passed;
    }
#endif
    for (unsigned int x = 0; x < n; ++x){
        if (a[x] != -1){
            passed = 0;
        }
        if (b[x] != -1){
            passed = 0;
        }
    }
    for (unsigned int x = 0; x < n / 10 + 1; ++x){
        if (c[x] != -1){
            passed = 0;
        }
    }
    for (unsigned int x = 0; x < n / 10 + 1; ++x){
        if (totals[x] != -1){
            passed = 0;
        }
    }
    for (unsigned int x = 0; x < 1; ++x){
        if (num_c[x] != -1){
            passed = 0;
        }
    }
    return passed;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + !(test1());
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}