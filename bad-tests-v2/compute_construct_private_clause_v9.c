#ifndef T1
//T1:parallel,loop,private,VIRTUAL,V:2.5-2.6
int test1(){
    int i, errors = 0, found = 0;
    real_t * a = (real_t *)malloc((n + 6) * sizeof(real_t));
    real_t b;

    for (i = 0; i < n + 6; ++i){
        a[i] = 3.0;
    }

    #pragma acc data copyin(a[0:n+6]) copy(b)
    {
        #pragma acc parallel
        {
            real_t bprivate = 1.0;
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                bprivate += a[i];
            }
            #pragma acc atomic capture
            {
                b = bprivate;
                bprivate = 0.0;
            }
        }
    }
    for (i = 0; i < n + 6; ++i){
        b += 3.0;
    }
    for (i = 0; i < n + 6; ++i){
        if (fabs(b - a[i]) < PRECISION){
            found++;
        }
    }
    if (found != 0){
        errors = 1;
        found = 0;
    }
    for (i = 0; i < n + 6; ++i){
        if (__srl_ispadding(a, i) && a[i] != 0){
            errors = 1;
        }
    }

    return errors;
}
#endif

#ifndef T2
//T2:parallel,loop,private,VIRTUAL,V:2.5-2.6
int test2(){
    int i, errors = 0, found = 0;
    real_t * a = (real_t *)malloc((n + 6) * sizeof(real_t));
    real_t b;

    for (i = 0; i < n + 6; ++i){
        a[i] = 1.0;
    }

    #pragma acc data copyin(a[0:n+6]) copy(b)
    {
        #pragma acc parallel
        {
            real_t bprivate = 1.0;
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                bprivate *= a[i];
            }
            #pragma acc atomic capture
            {
                b = bprivate;
                bprivate = 1.0;
            }
        }
    }
    for (i = 0; i < n + 6; ++i){
        b *= 1.0;
    }
    for (i = 0; i < n + 6; ++i){
        if (fabs(b - a[i]) < PRECISION){
            found++;
        }
    }
    if (found != 0){
        errors = 1;
        found = 0;
    }
    for (i = 0; i < n + 6; ++i){
        if (fabs(a[i] - 1.0) < PRECISION){
            found++;
        }
    }
    if (found != 0){
        errors = 1;
        found = 0;
    }


    return errors;
}
#endif

#ifndef T3
//T3:parallel,loop,private,VIRTUAL,V:2.5-2.6
int test3(){
    int i, errors = 0, x = 1;
    real_t * a = (real_t *)malloc((n + 6) * sizeof(real_t));
    bool error_in_loop = false;

    for (i = 0; i < n + 6; ++i){
        a[i] = 1.0;
    }

    #pragma acc data copyin(a[0:n+6]) copy(x)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                #pragma acc atomic
                    x += i;
                #pragma acc private(error_in_loop)
                {
                    //Elements in brackets should be set to an
                    //indeterminate value
                    error_in_loop = false;

                    #pragma acc loop
                    for (int j = i; j < n; ++j){
                        if (error_in_loop == false){
                            a[i] += (real_t) - 1 * (n - j);
                            error_in_loop = true;
                        }
                        else{
                            a[i] -= (real_t) - 2 * (n - j);
                            error_in_loop = false;
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < n + 6; ++i){
        x += 1;
    }
    for (i = 0; i < n + 6; i = i + 2){
        a[i] -= (real_t)(n + 1) * ((real_t)n / 2);
    }
    for (i = 1; i < n + 6; i = i + 2){
        a[i] += (real_t)(n + 1) * (((real_t)n + 1) / 2);
    }
    for (i = 0; i < n + 6; ++i){
        if (fabs(a[i]) < 2 * PRECISION){
            a[i] = 0;
        }
    }
    if (x != ((n / 2) * (n + 1)) + n + 1){
        errors = 1;
    }
    for (i = 0; i < n + 6; ++i){
        if (fabs(a[i]) > PRECISION){
            errors = 1;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
    return failcode;
}