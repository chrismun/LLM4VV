#ifndef T1
//T1:runtime,data,executable-data,V:2.0-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
        a[x] = 0.0;
        b[x] = 1.0;
        c[x] = 1.0;
    }

    devdata = (real_t *)acc_create(hostdata, 3 * n * sizeof(real_t));

    #pragma acc data copyin(b[0:n]) copyout(c[0:n])
    {
        acc_memcpy_to_device(&(devdata[2 * n]), c, n * sizeof(real_t));
        #pragma acc parallel present(a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + (b[x] + c[x]);
            }
        }
        acc_memcpy_from_device(c, &(devdata[2 * n]), n * sizeof(real_t));
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,V:2.0-2.7
int test2(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
        a[x] = 0.0;
        b[x] = 1.0;
        c[x] = 1.0;
    }

    devdata = acc_copyin(hostdata, 3 * n * sizeof(real_t));

    #pragma acc data copyin(b[0:n]) copyout(c[0:n])
    {
        acc_memcpy_to_device(&(devdata[2 * n]), c, n * sizeof(real_t));
        #pragma acc parallel present(a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + (b[x] + c[x]);
            }
        }
        acc_memcpy_from_device(c, &(devdata[2 * n]), n * sizeof(real_t));
    }

    acc_delete(hostdata, 3 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,V:2.0-2.7
int test3(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    devdata = acc_malloc(3 * n * sizeof(real_t));
    
    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
        a[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        b[x] = 1;
        c[x] = 1;
    }

    acc_memcpy_to_device(devdata, hostdata, 2 * n * sizeof(real_t));
    acc_memcpy_to_device(&(devdata[2 * n]), c, n * sizeof(real_t));

    #pragma acc data copyin(b[0:n]) present(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + (b[x] + c[x]);
            }
        }
    }

    acc_memcpy_from_device(c, &(devdata[2 * n]), n * sizeof(real_t)); 

    #pragma acc exit data delete(hostdata[0:3*n])
  
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,errors,data,ini-called,devonly,V:2.5-2.7
int test4(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * hostdata = (real_t *)malloc(3 * n * sizeof(real_t) );
    int * hasDevice = (int *)malloc(sizeof(int));
    real_t * devdata;
    hasDevice[0] = 1;

    #pragma acc data deviceptr(hostdata, devdata)
    {
        devdata = acc_copyin(hostdata, 3 * n * sizeof(real_t));
        #pragma acc enter data copyin(hostdata[0:3*n]) create(devdata[0:3*n])
        #pragma acc parallel present(devdata[0:3*n])
        {
            #pragma acc loop
            for (int x = 0; x < 3 * n; ++x){
                devdata[x] = hostdata[x];
            }
        }
        #pragma acc exit data delete(hostdata[0:3*n]) copyout(devdata[0:3*n])
        #pragma acc enter data copyin(hostdata[0:2*n]) create(devdata[0:2*n])
        acc_memcpy_to_device(devdata, &(devdata[n]), n * sizeof(real_t));
        #pragma acc enter data copyin(hostdata[0:n]) create(devdata[0:n])
        #pragma acc data copyout(c[0:n]) copyin(devdata[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = devdata[x] + b[x];
                }
            }
        }
        #pragma acc exit data delete(c[0:n]) copyout(devdata[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (hostdata[x] + b[x] )) > PRECISION){
            err += 1;
        }
    }

  return err;
}
#endif

#ifndef T5
//T5:runtime, data, ini, errors, devonly
int test5(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * hostdata = (real_t *)malloc(3 * n * sizeof(real_t) );
    int * hasDevice = (int *)malloc(sizeof(int));
    real_t *devdata;
    hasDevice[0] = 1;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
    }

    devdata = acc_copyin(hostdata, 3 * n * sizeof(real_t));    

    #pragma acc enter data deviceptr(devdata)
    #pragma acc parallel present(devdata[0:3*n])
    {
        #pragma acc loop
        for (int x = 0; x < 3 * n; ++x){
            devdata[x] = hostdata[x];
        }
    }
    #pragma acc exit data delete(hostdata[0:3*n]) copyout(devdata[0:3*n])
    #pragma acc enter data copyin(hostdata[0:2*n]) create(devdata[0:2*n])
    
        acc_memcpy_to_device(&(devdata[2 * n]), &(devdata[n]), n * sizeof(real_t));
    
    #pragma acc enter data copyin(hostdata[0:n]) create(devdata[0:n])
    #pragma acc data copyout(c[0:n]) copyin(devdata[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = devdata[x] + b[x];
            }
        }
    }
    #pragma acc exit data delete(hostdata[0:3*n]) delete(c[0:n])
    #pragma acc enter data deviceptr(c)
    #pragma acc parallel present(c[0:n])
    {
    #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = c[x] * hasDevice[0];
        }
    }
    #pragma acc exit data delete(c[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (hostdata[2 * n + x] + hostdata[x] * hasDevice[0]))) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:runtime, data,ini,errors,devonly
int test6(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * hostdata = (real_t *)malloc(3 * n * sizeof(real_t) );
    int * hasDevice = (int *)malloc(sizeof(int));
    real_t *devdata;
    hasDevice[0] = 1;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
    }

    devdata = acc_copyin(hostdata, 3 * n * sizeof(real_t));

    #pragma acc enter data deviceptr(devdata)
    #pragma acc parallel present(devdata[0:3*n])
    {
        #pragma acc loop
        for (int x = 0; x < 3 * n; ++x){
            devdata[x] = hostdata[x];
        }
    }
    #pragma acc exit data delete(hostdata[0:3*n]) copyout(devdata[0:3*n])
    #pragma acc enter data copyin(hostdata[0:2*n]) create(devdata[0:2*n])
    acc_memcpy_to_device(&(devdata[2 * n]), &(devdata[n]), n * sizeof(real_t)));
    #pragma acc enter data copyin(hostdata[0:n]) create(devdata[0:n])
    #pragma acc data copyout(c[0:n]) copyin(devdata[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = devdata[x] + b[x];
            }
        }
    }
    #pragma acc exit data delete(hostdata[0:3*n]) delete(c[0:n])
    #pragma acc enter data deviceptr(c)
    #pragma acc parallel present(c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = c[x] * hasDevice[0];
        }
    }
    #pragma acc exit data delete(c[0:n])
    for (int x = 0; x < n ; ++x){
        if (fabs(c[x] - (hostdata[2 * n + x] + b[x]))) {
            err += 1;
        }
    }

    return err;
}