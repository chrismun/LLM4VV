#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyout(c[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += a[x] + b[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}

    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }
    acc_delete(a, n * sizeof(real_t));
    acc_delete(b, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}

	#ifndef PREV_V
    acc_create(a, n * sizeof(real_t));
    acc_create(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }
    acc_copyout(a, n * sizeof(real_t));
    acc_copyout(b, n * sizeof(real_t));
    #else
    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }  
    #endif
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}

	#ifndef PREV_V 
    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }
    #else
    acc_create(a, n * sizeof(real_t));
    acc_create(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }
    acc_copyout(a, n * sizeof(real_t));
    acc_copyout(b, n * sizeof(real_t));
	#endif
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}


    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += a[x] + b[x];
                }
            }
        }
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
        #pragma acc exit data copyout(a[0:n], b[0:n])
    }  

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2 * (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test6(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}


    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += a[x] + b[x];
                }
            }
        }
        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
        #pragma acc exit data delete(a[0:n], b[0:n])
    }  

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2 * (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T7
//T7:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test7(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
	 real_t * b = (real_t *)malloc(n * sizeof(real_t));
	 real_t * c = (real_t *)malloc(n * sizeof(real_t));

	for (int x = 0; x < n; ++x){
		a[x] = rand() / (real_t)(RAND_MAX / 10);
		b[x] = rand() / (real_t)(RAND_MAX / 10);
		c[x] = 0.0;
	}

	#ifndef PREV_V 
    acc_copyin(a, n * sizeof(real_t));
    acc_copyin(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += a[x] + b[x];
                }
            }
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n])
    #else
    acc_create(a, n * sizeof(real_t));
    acc_create(b, n * sizeof(real_t));
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += a[x] + b[x];
                }
            }
        }
    }
    #pragma exit acc data delete(a[0:n], b[0:n])
	#endif
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2 * (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}