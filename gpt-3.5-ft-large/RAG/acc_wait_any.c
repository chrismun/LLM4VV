#ifndef T1
//T1:comm,wait,asyncs,construct-independent,V:2.0-2.7
int test1(){
  int err = 0;
  srand(SEED);
  real_t * a = (real_t *)malloc(n * sizeof(real_t));
  real_t * b = (real_t *)malloc(n * sizeof(real_t));
  real_t * c = (real_t *)malloc(n * sizeof(real_t));
  real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
  real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));

  for (int x = 0; x < n; ++x){
      a[x] = 0;
      a_copy[x] = 1;
      b[x] = 1;
      b_copy[x] = 1;
      c[x] = 0;
  }

  #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
  {
    #pragma acc parallel
    {
      #pragma acc loop
      for (int x = 0; x < n; ++x){
        a[x] = 1;
      }
      #pragma acc loop
      for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
      }
    }
    #pragma acc exit
    acc_async_synchronize(acc_get_device_num(acc_get_device_type()));
  }

  for (int x = 0; x < n; ++x){
    if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
      err += 1;
    }
  }

  for (int x = 0; x < n; ++x){
    if (a[x] != a_copy[x]){
      err += 1;
      break;
    }
  }

  for (int x = 0; x < n; ++x){
    if (b[x] != b_copy[x]){
      err += 1;
      break;
    }
  }

    return err;
}
#endif

#ifndef T2
//T2:comm,wait,asyncs,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
     }

    #pragma acc enter data copyin(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = a[x];
        b[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
        b_copy[x] = b[x];
    }

    #pragma acc data present(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    acc_exit_data(a[0:n],0,async);
    acc_exit_data(b[0:n],0,async);
    #pragma acc wait
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a_copy[x] + b_copy[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:comm,wait,asyncs,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = 0;
            b[x] = 0;
        }

        for (int x = 0; x < n; ++x){
            a[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
            a_copy[x] = a[x];
            b[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
            b_copy[x] = b[x];
        }

        #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
            #pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n])
        }
        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a_copy[x] + b_copy[x])) > PRECISION){
                err += 1;
            }
        }
    }
    else {
        err += n;
    }

    return err;
}
#endif

#ifndef T4
//T4:comm,wait,asyncs,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        a_copy[x] = 0;
        b[x] = 0;
        b_copy[x] = 0;
        c[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        a_copy[x] = 1;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) {
            err += 1;
        }
    }

    srand(SEED);
    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = 0;
            b[x] = 0;
        }

        for (int x = 0; x < n; ++x){
            a[x] = 2;
            b[x] = 3;
            a_copy[x] = 2;
            b_copy[x] = 3;
        }

        #pragma acc data present(a[0:n], b[0:n]) copyout(c[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a_copy[x] + b_copy[x]) > PRECISION)) {
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:comm,wait,asyncs,construct-independent,reference,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] * b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * b[x]))) {
            err += 1;
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
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}