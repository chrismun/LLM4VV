#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest = (real_t *)malloc(4 * n * sizeof(real_t));
    int * devtest_present = (int *)malloc(4 * sizeof(int) * n);
    int * host_present = (int *)malloc(4 * sizeof(int) * n);
    int errors[4];

    for (int x = 0; x < n; ++x){
        host_present[x] = 1;
        devtest_present[x] = 0;
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n]) async(1)

    for (int y = 0; y < a_large; y+= 1024){
      for (int x = 0; x < 4 * n; ++x){
        devtest[x] = rand() / (real_t)(RAND_MAX / 10);
      }
      #pragma acc enter data copyin(devtest[0:4*n]) async(y)
      for (int x = 0; x < n; ++x){
        devtest_present[n * 0 + x] = 1;
        devtest_present[n * 1 + x] = 1;
        devtest_present[n * 2 + x] = 1;
        devtest_present[n * 3 + x] = 1;
      }
    }

    for (int y = 0; y < a_large; y+= 1024){
      for (int x = 0; x < 4 * n; ++x){
        host_present[n * 0 + x] = 0;
        host_present[n * 1 + x] = 0;
        host_present[n * 2 + x] = 0;
        host_present[n * 3 + x] = 0;
      }
      #pragma acc parallel async(y) present(c[0:n])
      {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
          c[x] = c[x] + a[x] + b[x];
        }
      }
    }

    #pragma acc exit data copyout(c[0:n]) async(1)

    for (int y = 0; y < a_large; y+= 1024){
      #pragma acc exit data delete(devtest[0:4*n]) async(y)
    }

    for (int x = 0; x < n; ++x){
      	d[x] = c[x];
        c[x] = 0;
    }

    for (int x = 0; x < (4 * n); ++x){
        if (devtest_present[x] - host_present[x] != 0){
          errors[x % n] = 1;
        }
        else {
          errors[x % n] = 0;
        }
      }

    for (int x = 0; x < n; ++x){
      for (int y = 0; y < 4; y++){
        if (errors[x] == 1){
        err += errors[x];
       }
      }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x]))) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest = (real_t *)malloc(4 * n * sizeof(real_t));
    int * devtest_present = (int *)malloc(4 * sizeof(int) * n);
    int * host_present = (int *)malloc(4 * sizeof(int) * n);
    int errors[4];

    for (int x = 0; x < 4 * n; ++x){
      devtest[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    for (int x = 0; x < n; ++x){
        a[x] = devtest[x * 2];
        b[x] = devtest[x * 2 + 1];
        c[x] = 0;
    }
    for (int x = 0; x < 4 * n; ++x){
      host_present[x] = 1;
      devtest_present[x] = 1;
    }

    #pragma acc data copyin(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] * c[x];
            }
        }
    }

    for (int x = 0; x < 4 * n; ++x){
      errors[x] = 0;
    }

    for (int x = 0; x < 4 * n; ++x){
      for (int y = 0; y < 4 * n; ++y ){
        if (fabs(devtest[x] - (sqrt(a[y]) * sqrt(a[y]) + sqrt(b[y]) * sqrt(b[y])))) < PRECISION * 4 * n){
            errors[x] = 1;
            break;
        }
      }
      if (errors[x] == 0){
        err++;
      }
    }

    for (int x = 0; x < 4 * n ; ++x){
      if (devtest_present[x] - host_present[x] != 0){
        errors[x] = 1;
      }
    }

    for (int x = 0; x < n; ++x){
      if (errors[x] == 1){
        err++;
      }
    }
    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,devonly,construct-independent,reference-counting,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest = (real_t *)malloc(4 * n * sizeof(real_t));
    int * devtest_present = (int *)malloc(4 * sizeof(int) * n);
    int * host_present = (int *)malloc(4 * sizeof(int) * n);

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc data create(devtest[0:4*n])
        {
            #pragma acc enter data copyin(c[0:n]) create(a[0:n], b[0:n]) async(1)
            for (int x = 0; x < 8; ++x){
                for (int y = 0; y < n; ++y){
                    devtest[x * n + y] = a[y] * b[y];
                }
            }
            for (int x = 0; x < 8; ++x){
                #pragma acc enter data copyin(devtest[x * n:n]) async(x + 10)
            }
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < 10 * n; ++x){
                    c[x % n] = c[x % n] + devtest[x];
                }
            }
        }
    }

    for (int x = 0; x < 8 * n; ++x){
        devtest_present[x] = 0;
        host_present[x] = 1;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * b[x] * 18))) > PRECISION * n){
            err = err + 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,devonly,construct-independent,reference-counting,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest = (real_t *)malloc(4 * n * sizeof(real_t));
    int * devtest_present = (int *)malloc(4 * sizeof(int) * n);
    int * host_present = (int *)malloc(4 * sizeof(int) * n);

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        for (int x = 0; x < 2; ++x){
            #pragma acc data copy(a[0:n], b[0:n]) create(devtest[0:n])
            {
                #pragma acc enter data copyin(c[0:n]) async(1)
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int x = 0; x < n; ++x){
                        c[x] += a[x] + b[x];
                    }
                }
                #pragma acc exit data copyout(c[0:n]) async(1)
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int x = 0; x < n; ++x){
                        devtest[x] = c[x] * 2;
                    }
                }
                #pragma acc enter data copyin(devtest[0:n]) async(10)
                #pragma acc exit data delete(devtest[0:n]) async(10)
            }
        }
    }

    for (int x = 0; x < 2 * n; ++x){
        host_present[x] = 1;
        devtest_present[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]) * 10)) > PRECISION * n{
            err += 1;
        }
    }

    for (int x = 0; x < 2 * n; ++x){
      if (host_present[x] != devtest_present[x]){
        err += 1;
      }
    }

    return err;
}