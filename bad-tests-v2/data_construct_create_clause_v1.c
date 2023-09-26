#ifndef T1
//T1:data,data-region,construct-independent,create,compatibility-20,reference-counting,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));

	for (int x = 0; x < 10 * n; ++x){
        a[x] = 3;
        b[x] = 1;
    }

	#pragma acc enter data create(a[0:10 * n])

    for (int x = 0; x < 10; ++x){
    	for (int y = 1; y < n; ++y){
            b[x * n + y] = b[x * n + y - 1] * .5;
        }
    }

	#pragma acc data present(a[0:10*n])
    {
        for (int x = 0; x < 10; ++x){
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    a[x * n + y] += b[x * n + y];
                }
            }
        }
    }

	for (int x = 0; x < 10 * n; ++x){
        if (fabs(a[x] - (b[x] + 3)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:data,data-region,construct-independent,create,compatibility-20,reference-counting,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 3;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

	#pragma acc enter data create(a[0:10*n])

	#pragma acc data present(a[0:10*n])
    {
        for (int x = 0; x < 10; ++x){
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < 10 * n; ++y){
                    a[x * n + y] += b[x * n + y];
                }
            }
        }
	}

	#pragma acc exit data copyout(a[0:10*n])

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(a[x] - (b[x] + 3)) > PRECISION){
            err += 1;
        }
    }
    return err;
}
#endif

#ifndef T3
//T3:data,data-region,construct-independent,create,compatibility-20,reference-counting,if,devonly,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
 	
	devtest[0] = acc_get_device_type() == acc_device_nvidia;

    if (n > 10){
    	for (int x = 0; x < 10 * n; ++x){
            a[x] = 3;
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(a[0:10*n])

        for (int x = 0; x < 10; ++x){
            for (int y = 1; y < n; ++y){
                b[x * n + y] = b[x * n + y - 1] * .5;
            }
        }

        #pragma acc data present(a[0:10*n])
        {
            for (int x = 0; x < 10; ++x){
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        a[x * n + y] += b[x * n + y];
                    }
                }
            }
        }

        #pragma acc exit data copyout(a[0:10*n])

        for (int x = 0; x < 10 * n; ++x){
            if (fabs(a[x] - (3)) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:data,data-region,construct-independent,create,compatibility-20,reference-counting,if,devonly,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
 	
    for (int x = 0; x < 10 * n; ++x){
        a[x] = 1;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    devtest[0] = acc_get_device_type() == acc_device_nvidia;

	#pragma acc enter data create(a[0:10*n]) if(devtest[0])

    for (int x = 0; x < 10; ++x){
        for (int y = 1; y < n; ++y){
            b[x * n + y] = b[x * n + y - 1] * .5;
        }
    }

    #pragma acc data present(a[0:10*n]) if(devtest[0])
    {
        for (int x = 0; x < 10; ++x){
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    a[x * n + y] += b[x * n + y];
                }
            }
        }
    }

    #pragma acc exit data copyout(a[0:10*n]) if(devtest[0])

	/* This normalization region is necessary so that we do not need to
	 * call normalize at the end of each test case. We are testing
	 * strict normalization here, but since the computed values are not
	 * independent from the discarded device's a values, we cannot
	 * perform strict normalization in pass.
	 */
	for (int x = 0; x < 10; ++x){
		for (int y = 0; y < n; ++y){
			a[x * n + y] = 1;
		}
	}
        

    return err;
}
#endif

#ifndef T5
//T5:data,data-region,construct-independent,create,compatibility-20,reference-counting,if,devonly,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = acc_get_device_type() == acc_device_nvidia;

	a = (real_t *)malloc(20 * n * sizeof(real_t));
	b = (real_t *)malloc(20 * n * sizeof(real_t));

    for (int x = 0; x < 20 * n; ++x){
        a[x] = 3;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

	#pragma acc enter data create(a[0:10*n]) if(devtest[0])

	#pragma acc enter data create(a[0:10*n]) if(devtest[0])

	#pragma acc data present(a[0:10*n]) if(devtest[0])
	{
                for (int x = 0; x < 10; ++x){
                    #pragma acc parallel
                    {
                        #pragma acc loop
                        for (int y = 0; y < n; ++y){
                            a[x * n + y] += b[x * n + y];
                        }
                    }
                }
     }

	#pragma acc exit data copyout(a[0:10*n]) if(devtest[0])

	for (int x = 0; x < 20 * n; ++x){
		if (fabs(a[x] - (3)) > PRECISION){
			err += 1;
		}
	}

	#pragma acc data present(a[0:10*n], b[0:10*n]) copyout(a[0:10*n])
	{
		for (int x = 0; x < 10; ++x){
			#pragma acc parallel
			{
				#pragma acc loop
				for (int y = 0; y < n; ++y){
					a[x * n + y] += b[x * n + y];
				}
			}
		}
	}

    for (int x = 0; x < 20 * n; ++x){
        if (fabs(a[x] - (3 + b[x]))) > PRECISION)){
            err += 1;
        }
    }

	/* This normalization region is necessary so that we do not need to
	 * call normalize at the end of each test case. We are testing
	 * strict normalization here, but since the computed values are not
	 * independent from the discarded device's a values, we cannot
	 * perform strict normalization in pass.
	 */
	for (int x = 0; x < 10; ++x){
		for (int y = 0; y < n; ++y){
			a[x * n + y] = 1;
		}
	}

    return err;
}
#endif

#ifndef T6
//T6:data,data-region,construct-independent,create,compatibility-20,reference-counting,deviceonly,V:2.0-2.7
int test6(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = acc_get_device_type() == acc_device_nvidia;

    if (devtest[0] == 1){
        for (int x = 0; x < 10 * n; ++x){
            a[x] = 3;
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(a[0:10*n]) deviceptr(a)

        for (int x = 0; x < 10; ++x){
            for (int y = 1; y < n; ++y){
                b[x * n + y] = b[x * n + y - 1] * .5;
            }
        }

        #pragma acc data present(a[0:10*n])
        {
            for (int x = 0; x < 10; ++x){
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        a[x * n + y] += b[x * n + y];
                    }
                }
            }
        }

        for (int x = 0; x < 10 * n; ++x){
            if (fabs(a[x] - (3 + b[x]))) > PRECISION)){
                err += 1;
            }
        }

        #pragma acc exit data copyout(a[0:10*n])


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
#ifndef T6
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test6();
    }
    if (failed != 0){
        failcode = failcode + (1 << 5);
    }
#endif
    return failcode;
}