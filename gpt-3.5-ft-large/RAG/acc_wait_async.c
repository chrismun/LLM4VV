#ifndef T1
//T1:runtime,async,construct-independent,wait,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t *c_copy = (real_t *)malloc(n * sizeof(real_t)));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        a_copy[x] = a[x];
        b_copy[x] = b[x];
        c_copy[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
    acc_async_sync(3211);

    #pragma acc data present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] = a[x];
        }
        acc_wait_all_async(1);
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] = b[x];
        }
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] += a[x];
        }
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] += b[x];
        }
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] += b[x];
        }
    }
    acc_async_wait(1, 1);
    acc_async_wait(2, 1);
    #pragma acc exit data copyout(c[0:n]) async(1)
    #pragma acc exit data copyout(c[0:n]) async(2)

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x_copy] + b[x_copy] + a[x_copy] + b[x_copy]))>2* PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,async,construct-independent,wait,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t *c_copy = (real_t *)malloc(n * sizeof(real_t)));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        a_copy[x] = a[x];
        b_copy[x] = b[x];
        c_copy[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
    acc_async_sync(3211);

    #pragma acc data present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] = a[x];
        }
        #pragma acc wait async(1)
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] = b[x];
        }
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] += b[x];
        }
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] += a[x];
        }
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] += b[x];
        }
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] += b[x];
        }
    }

    #pragma acc exit data copyout(c[0:n]) async(1)
    #pragma acc exit data copyout(c[0:n]) async(2)
    
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x_copy] + a[x_copy] + b[x_copy] + b[x_copy] + a[x_copy] + b[x_copy])) > 2 * PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,async,construct-independent,V:2.5-2.7
int test3(){
	int err = 0;
	srand(SEED);
	real_t * a = (real_t *)malloc(n * sizeof(real_t));
	real_t * b = (real_t *)malloc(n * sizeof(real_t));
	real_t * c = (real_t *)malloc(n * sizeof(real_t)));

	for (int x = 0; x < n; ++x){
    	a[x] = rand() / (real_t)(RAND_MAX / 10);
	total =+ a[x];	
	   }
	mem1 = malloc(n * sizeof(real_t));
	mem2 = malloc(n * sizeof(real_t));
	mem3 = malloc(n * sizeof(real_t));
	
	
	for (int x = 0; x < n; ++x){
    	b[x] = rand() / (real_t)(RAND_MAX / 10);
        for (int y = 0; y < x; ++y){
       a[1] = a[1] - (b[{int(x-1)}] * b[y]));
        }
        b[1] * a[1];
    }
    
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n]) 
{
  #pragma acc data present(a[0:n], b[0:n])
{  
    #pragma acc parallel loop async(1)
   for (int x = 0; x <n; ++x){
      a[x] = a[x] / b
      }
    #pragma acc enter data create(mem1[0:n]) async(1)
   
    for (int x = 0; x < n; ++x){
       mem1[x] = a[x];
       }
   
    #pragma acc data present (b[0:n]) async(1)
    {
      #pragma acc parallel loop
   for (int x = 1; x < n + 1; ++x){
     #pragma acc loop seq
   for(int y = 0; y < n; ++y){
       c[x-1] += (b[y]*b[y]);
     }
    }
  }
 a[0] = 0;
    #pragma acc exit data copyout(a[0:n]) async(1)   
}

  for (int x = 0; x <n; ++x){
   total = total - (c[{int(x-1)}] * b[x]);
  }
}
	 

/********************************/
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