#ifndef T1
//T1:data,data-region,construct-independent,reference-counting,V:2.0-2.7
int test1(){
	int err = 0;
	srand(SEED);
	int *a = (int *)malloc(n * sizeof(int));
	int *b = (int *)malloc(n * sizeof(int));
	int *c = (int *)malloc(n * sizeof(int));

	for (int x = 0; x < n; ++x){
		a[x] = 1;
		b[x] = 2;
		c[x] = 0;
	}

	#pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n])
	#pragma acc parallel present(a[0:n], b[0:n], c[0:n])
	{
		#pragma acc loop
		for (int x = 0; x < n; ++x){
			c[x] = a[x] + b[x];
		}
	}
	#pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n])
    
	for (int x = 0; x < n; ++x){
		if (c[x] != 3) {
			err += 1;
			break;
		}
	}
	free(a);
	free(b);
	free(c);
	if (acc_is_present(a, n * sizeof(int)) == acc_present)
		err += 1;
	if (acc_is_present(b, n * sizeof(int)) == acc_present)
		err += 1;

	return err;
}
#endif

#ifndef T2
//T2:data,data-region,construct-independent,reference-counting,devonly,V:2.0-2.7
int test2(){
	int err = 0;
	srand(SEED);
	real_t *a = (real_t *)malloc(n * sizeof(real_t));
	real_t *b = (real_t *)malloc(n * sizeof(real_t));
	real_t *c = (real_t *)malloc(n * sizeof(real_t));
	real_t *devtest = (real_t *)malloc(1 * sizeof(real_t));
    devtest[0] = 1.0;
	
	for (int x = 0; x < n; ++x){
		a[x] = 1.5;
		b[x] = 2.5;
		c[x] = 0;
	}

	#pragma acc enter data copyin(a[0:n], b[0:n])
	#pragma acc enter data copyin(devtest[0:1])
	#pragma acc parallel present(a[0:n], b[0:n], c[0:n])
	{
		#pragma acc loop
		for (int x = 0; x < n; ++x){
			c[x] = a[x] + b[x];
		}
	}
    if (fabs(c[(int)n/2] - 4) > PRECISION){
        err++;
    }
	#pragma acc exit data copyin(devtest[0:1]) delete(a[0:n], b[0:n]) copyout(c[0:n])

	for (int x = 0; x < n; ++x){
		if (fabs(c[x] - 3) > PRECISION){
			err += 1;
		}
	}
	free(a);
	free(b);
	free(c);

	return err;
}
#endif

#ifndef T3
//T3:data,data-region,construct-independent,reference-counting,devonly,V:1.0-2.7
int test3(){
	int err = 0;
	srand(SEED);
	real_t *a = (real_t *)malloc(n * sizeof(real_t));
	real_t *b = (real_t *)malloc(n * sizeof(real_t));
	real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *devtest = (real_t *)malloc(1 * sizeof(real_t));
    devtest[0] = 1.0;

	for (int x = 0; x < n; ++x){
		a[x] = 1.5;
		b[x] = 2.5;
		c[x] = 0;
	}

	#pragma acc enter data copyin(a[0:n], b[0:n])
	#pragma acc enter data copyin(devtest[0:1])
	#pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
		for (int x = 0; x < n; ++x){
			c[x] = c[x] + devtest[0];
		}
    }
    if (fabs(c[(int)n/2] - 1.0) > PRECISION){
        err++;
    }
	#pragma acc exit data copyin(devtest[0:1]) delete(a[0:n], b[0:n]) copyout(c[0:n])

	for (int x = 0; x < n; ++x){
		if (fabs(c[x]) > PRECISION){
			err += 1;
		}
	}
	free(a);
	free(b);
	free(c);
	
	return err;
}
#endif

#ifndef T4
//T4:data,data-region,construct-independent,reference-counting,devonly,V:2.7
int test4(){
	int err = 0;
	srand(SEED);
	real_t *a = (real_t *)malloc(n * sizeof(real_t));
	real_t *b = (real_t *)malloc(n * sizeof(real_t));
	real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *devtest1 = (real_t *)malloc(1 * sizeof(real_t));
    real_t *devtest2 = (real_t *)malloc(1 * sizeof(real_t));
    devtest1[0] = 3.0;
    devtest2[0] = 5.0;


	for (int x = 0; x < n; ++x){
		a[x] = 1.5;
		b[x] = 1.5;
		c[x] = 0;
	}

	#pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc enter data copyin(devtest1[0:1])
    #pragma acc enter data copyin(devtest2[0:1])
	#pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = c[x] + devtest1[0] + devtest2[0];
        }
    }
	for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 9.0) > PRECISION){
            err++;
        }
    }
	#pragma acc exit data copyin(devtest1[0:1]) copyin(devtest2[0:1]) delete(a[0:n], b[0:n]) copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x]) > PRECISION){
            err++;
        }
    }
	free(a);
	free(b);
	free(c);

    return err;
}
#endif

#ifndef T5
//T5:data,data-region,construct-independent,reference-counting,pcopyin,devonly,V:2.7-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *devtest1 = (real_t *)malloc(1 * sizeof(real_t));
    real_t * devtest2 = (real_t *)malloc(1 * sizeof(real_t));
    devtest1[0] = 1.0;
    devtest2[0] = 3.0;

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc enter data copyin(devtest1[0:1])
    #pragma acc enter data copyin(devtest2[0:1])
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = c[x] + a[x] + b[x] + devtest1[0];
        }
    }
    #pragma acc exit data pcopyin(devtest1[0:1]) copyin(devtest2[0:1])
    #pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n])
    
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (4 + devtest1[0])) > PRECISION){
            err++;
        }
    }
    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int errorcode = 0;
    int failcode;
#ifndef T1
    int failed;
    failed = 0;
    failcode = 1 << 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        errorcode = errorcode + failcode;
    }
#endif
#ifndef T2
    int failed;
    failed = 0;
    failcode = 1 << 1;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        errorcode = errorcode + failcode;
    }
#endif
#ifndef T3
    int failed;
    failed = 0;
    failcode = 1 << 2;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        errorcode = errorcode + failcode;
    }
#endif
#ifndef T4
    int failed;
    failed = 0;
    failcode = 1 << 3;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        errorcode = errorcode + failcode;
    }
#endif
#ifndef T5
    int failed;
    failed = 0;
    failcode = 1 << 4;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        errorcode = errorcode + failcode;
    }
#endif
    return errorcode;
}