#ifndef T1
//T1:parallel,private,reduction,V:combined-constructs,loop,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 1.0;
        c[x] = 1.0;
    }

    #pragma acc data copy(a[0:n]) copyout(b[0:n]) copyin(c[0:n])
    {
        #pragma acc parallel loop private(a) reduction(+:c[0:n])
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
            c[x] += a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err = 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:serial,private,reduction,V:combined-constructs,loop,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 1.0;
        c[x] = 1.0;
    }

    #pragma acc data copy(a[0:n]) copyout(b[0:n]) copyin(c[0:n])
    {
        #pragma acc serial loop private(a) reduction(+:c[0:n])
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
            c[x] += a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err = 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:loop,devonly,private,reduction,V:2.7-2.7
int test3(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int isHost = 1;

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 1.0;
        c[x] = 1.0;
    }

    #pragma acc data copy(a[0:n]) copy(b[0:n]) copyin(c[0:n])
    {
        #pragma acc kernels loop private(a) reduction(+:c[0:n])
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
            c[x] += a[x];
        }
        isHost = acc_is_host(c);
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err = 1;
        }
    }

    if (isHost){
        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - 1.0) > PRECISION){
                err = 1;
            }
        }
    }
    else {
        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - 2.0) > PRECISION){
                err = 1;
            }
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
    return failcode;
}