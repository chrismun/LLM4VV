#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    real_t *h_a = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_c = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_d = (real_t *)malloc(n * sizeof(real_t));
    real_t temp = 0.0;
    int i;

    for (i = 0; i < n; ++i){
        h_a[i] = rand() / (real_t)(RAND_MAX / 10);
        h_b[i] = rand() / (real_t)(RAND_MAX / 10);
        h_c[i] = 0.0;
        h_d[i] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(h_a[0:n], h_b[0:n], h_d[0:n])
    {
        #pragma acc data copy(h_c[0:n])
        {
            #pragma acc update device(h_c[0:n])
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < n; ++i){
                    h_c[i] = h_a[i] + h_b[i];
                }
            }
            #pragma acc update self(h_c[0:n])
        }
        #pragma acc data copy(h_a[0:n], h_b[0:n])
        {
            #pragma acc update device(h_a[0:n], h_b[0:n])
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < n; ++i){
                    h_a[i] = h_a[i] + h_d[i];
                    h_b[i] = h_b[i] + h_d[i];
                }
            }
            #pragma acc update self(h_a[0:n], h_b[0:n])
        }
    }

    for (int i = 0; i < n; ++i){
        temp = fmax(temp, fabs(h_c[i] - (h_a[i] + h_b[i]))));
    }
    if (temp > 2* PRECISION){
        err += 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    real_t *h_a = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_c = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_d = (real_t *)malloc(n * sizeof(real_t));
    real_t temp = 0.0;

    for (int nl = 0; nl < 10; ++nl){
        for (int i = 0; i < n; ++i){
            h_a[i] = 0.0;
            h_b[i] = rand() / (real_t)(RAND_MAX / 10);
            h_c[i] = rand() / (real_t)(RAND_MAX / 10);
            h_d[i] = rand() / (real_t)(RAND_MAX / 10);
        }
        temp = 0.0;

        #pragma acc data copyin(h_b[0:n], h_c[0:n], h_d[0:n]) copyout(h_a[0:n])
        {
            for (int i = 0; i < n; ++i){
                h_a[i] = 0.0;
            }
            #pragma acc data copy(h_a[0:n]) 
            {
                #pragma acc update device(h_a[0:n])
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int i = 0; i < n; ++i){
                        h_a[i] += h_c[i] + h_b[i];
                    }
                }
                #pragma acc update self(h_a[0:n])
            }
            #pragma acc parallel 
            {
                #pragma acc loop
                for (int i = 0; i < n; ++i){
                    h_a[i] += h_d[i];
                }
            }
        }

        for (int i = 0; i < n; ++i){
            temp += fabs(h_a[i] - (h_b[i] + h_c[i] + h_d[i])));
        }
        if (temp > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    real_t *h_a = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_c = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_d = (real_t *)malloc(n * sizeof(real_t));
    int *devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int nl = 0; nl < 10; ++nl){
            for (int i = 0; i < n; ++i){
                h_a[i] = rand() / (real_t)(RAND_MAX / 10);
                h_c[i] = 0.0;
                h_b[i] = rand() / (real_t)(RAND_MAX / 10);
                h_d[i] = rand() / (real_t)(RAND_MAX / 10);
            }

            #pragma acc data copyin(h_a[0:n], h_b[0:n], h_d[0:n])
            {
                for (int i = 0; i < n; ++i){
                    h_a[i] = 0.0;
                }
                #pragma acc data copy(h_a[0:n])
                {
                    #pragma acc update device(h_a[0:n])
                    for (int i = 0; i < n; ++i){
                        h_c[i] = h_a[i] + h_b[i] + h_d[i];
                    }
                }
                for (int i = 0; i < n; ++i){
                    if (fabs(h_a[i] - (h_b[i] + h_d[i]))) > PRECISION{
                        err += 1;
                    }
                }
            }

            #pragma acc data copyin(h_b[0:n], h_d[0:n]) copyout(h_c[0:n])
            {
                #pragma acc data copy(h_c[0:n])
                {
                    #pragma acc update device(h_c[0:n])
                    for (int i = 0; i < n; ++i){
                        h_c[i] += h_b[i] + h_d[i];
                    }
                }
                #pragma acc update self(h_c[0:n])
            }

            for (int i = 0; i < n; ++i){
                if (fabs(h_c[i] - (2 * (h_a[i] + h_b[i] + h_d[i])))) > 2 * PRECISION){
                    err += 1;
                }
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,construct-independent,partial,V:2.5-2.7
int test4(){
    int err = 0;
    int *devtest = (int *)malloc(sizeof(int));
    real_t * h_a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * h_b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * h_c = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * h_d = (real_t *)malloc(n * sizeof(real_t));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < 2; ++x){
            for (int nl = 0; nl < 10; ++nl){
                for (int i = 0; i < n; ++i){
                    h_a[n * nl + i] =  0.0;
                    h_b[n * nl + i] =  2.0;
                    h_d[i] = 1.0;
                }
            }

            #pragma acc data copyin(h_b[0:10*n], h_d[0:n]) copyout(h_c[0:10*n]) copy(h_a[0:10*n])
            {
                for (int x = 0; x < 2; ++x){
                    #pragma acc parallel loop
                    for (int nl = 0; nl < 10; ++nl){
                        for (int i = 0; i < n; ++i){
                            h_a[n * nl + i] += h_b[n * nl + i] + (x + 1);
                        }
                    }
                }
                #pragma acc update host(h_a[0:10*n])
                for (int i = 0; i < 10 * n; ++i){
                    if (fabs(h_a[i]) > PRECISION){
                        err += 1;
                    }
                }
  
                #pragma acc parallel loop
                for (int x = 0; x < 2; ++x){
                    #pragma acc parallel loop
                    for (int nl = 0; nl < 10; ++nl){
                        for (int i = 0; i < n; ++i){
                            h_a[n * nl + i] += h_b[n * nl + i];
                        }
                    }
                }
                #pragma acc update host(h_a[0:10*n])
                for (int nl = 0; nl < 10; ++nl){
                    for (int i = 0; i < n; ++i){
                        if (fabs(h_a[n * nl + i] - (3.0 + h_b[n * nl + i]))) > PRECISION{
                            err += 1;
                        }
                    }
                }
            }
        }
    }

    return err;
}