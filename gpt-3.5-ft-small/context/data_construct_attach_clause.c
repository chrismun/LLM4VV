#include "acc_testsuite.h"
#ifndef T1
//T1:data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        c[x + n] = 1;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:2*n])
    #pragma acc data create(c[0:2*n]) copyout(c[0:n]) copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
                c[x + n] += a[x] + b[x];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n]) delete(c[0:2*n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (c[x] - 1)) > PRECISION) {
            err += 1;
        }
        if (fabs(b[x] - (c[x + n] - 1)) > PRECISION) {
            err += 1;
        }
    }
  
    return err;
}
#endif

#ifndef T2
//T2:data,construct-independent,executable-data,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        c[x + n] = 1;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) attach_present(c[0:n]) create(c[0:n])
    #pragma acc data create(c[0:n]) copyout(c[0:n]) copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            real_t* firstCPtr = c;
            real_t* secondCPtr = c + n;
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                firstCPtr[x] += a[x] + b[x];
                secondCPtr[x] += a[x] + b[x];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n]) detach(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (c[x] - 1)) > PRECISION){
            err += 1;
        }
        if (fabs(b[x] - (c[x + n] - 1)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:data,executable-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        c[x + n] = 1;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:2*n])
    #pragma acc parallel present(c[0:n])
    {
      #pragma acc loop
      for (int x = 0; x < n; ++x){
        c[x] += a[x] + b[x];
      }
    }
    #pragma acc parallel
    {
      #pragma acc loop private(err)
      for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (2 + a[x] + b[x])) > PRECISION){
          err += 1;
        }
      }
      #pragma acc loop private(err)
      for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (c[x] - 1)) > PRECISION){
          err += 1;
        }
        if (fabs(b[x] - 1) > PRECISION){
          err += 1;
        }
      }
    }
    
    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n]) delete (c[0:2 * n])
    if (err > 0){
      return 1;
    }
    else{
      return 0;