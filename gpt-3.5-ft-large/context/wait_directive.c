#ifndef T1
//T1:wait,async,V:2.5-2.7
int test1(){
	int err = 0;
        srand(SEED);
	size_t  n = n;
	real_t * a = (real_t *)malloc(n * sizeof(real_t));
        real_t * b = (real_t *)malloc(n * sizeof(real_t));
        real_t * c = (real_t *)malloc(n * sizeof(real_t));
        real_t * b_host = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                b[x] = rand() / (real_t)(RAND_MAX / 10);
                b_host[x] = b[x];
                c[x] = 1;
        }

	#pragma acc data copyin(a[0:n]) copy(b[0:n]) copyout(c[0:n])
	{
		#pragma acc parallel loop async(1)
		for (int x = 0; x < n; ++x){
			b[x] = b[x] * 2;
		}
		#pragma acc parallel loop async(2)
		for (int x = 0; x < n; ++x){
			c[x] = a[x] + b[x];
		}
		#pragma acc wait(1)
	}

        for (int x = 0; x < n; ++x){
                if (fabs(c[x] - (a[x] + b_host[x]))) > PRECISION){
                        err += 1;
                }
        }

	return err;
}
#endif

#ifndef T2
//T2:wait,async,V:2.5-2.7
int test2(){
        int err = 0;
        srand(SEED);
        size_t  n = n;
        real_t * a = (real_t *)malloc(n * sizeof(real_t));
        real_t * b = (real_t *)malloc(n * sizeof(real_t));
        real_t * c = (real_t *)malloc(n * sizeof(real_t));
        real_t * b_host = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                b[x] = rand() / (real_t)(RAND_MAX / 10);
                b_host[x] = b[x];
                c[x] = 1;
        }

        #pragma acc data copyin(a[0:n]) copy(b[0:n]) copyout(c[0:n])
        {
                #pragma acc parallel loop async(1)
                for (int x = 0; x < n; ++x){
                        b[x] = b[x] * 2;
                }
		#pragma acc wait
                #pragma acc parallel loop async(2)
                for (int x = 0; x < n; ++x){
                        c[x] = a[x] + b[x];
                }
        }

        for (int x = 0; x < n; ++x){
                if (fabs(b_host[x] - b[x]/2) > PRECISION){
                        err += 1;
                }
                if (fabs(c[x] - (a[x] + b[x])) > 2 * PRECISION){
                        err += 1;
                }
        }

        return err;
}
#endif

#ifndef T3
//T3:wait,async,V:2.5-2.7
int test3(){
	int err = 0;
        srand(SEED);
        size_t  n = n;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));
        real_t *c = (real_t *)malloc(n * sizeof(real_t));
        real_t *b_host = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                b[x] = rand() / (real_t)(RAND_MAX / 10);
                b_host[x] = b[x];
		c[x] = 0;
        }

	#pragma acc data copyin(a[0:n]) copy(b[0:n]) copyout(c[0:n])
	{
		#pragma acc parallel loop async(1)
		for (int x = 0; x < n; ++x){
			b[x] = b[x] * 2;
		}
		#pragma acc parallel loop async(1)
		for (int x = 0; x < n; ++x){
			b[x] = b[x] / 2;
		}
		#pragma acc parallel loop async(2)
		for (int x = 0; x < n ;++x){
			c[x] = a[x] + b[x];
		}
		#pragma acc wait
	}

	for (int x = 0; x < n; ++x){
		if (fabs(c[x] - (a[x] + 2 * b_host[x])) > PRECISION){
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
	test1();
        if (failcode == 1){
        	failed = 1;
        }
#endif
#ifndef T2
        failed = 0;
        failed = test2();
        if (failed != 0){
                failcode += (1 << 1);
        }
#endif
#ifndef T3
        failed = 0;
        failed = test3();
        if (failed != 0){
                failcode += (1 << 2);
        }
#endif
        return failcode;
}