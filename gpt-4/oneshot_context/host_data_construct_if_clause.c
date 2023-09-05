#ifndef T2
//T2:parallel,data,host_data,if_clause,V:1.0-2.7

int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * d_a;
    real_t * d_b;
    
    for(int x = 0; x < n; ++x){
        a[x] = rand() / (real_t) (RAND_MAX / 10);
    }

    d_a = acc_copyin(a, n * sizeof(real_t));
    d_b = acc_create(b, n * sizeof(real_t));
    #pragma acc host_data use_device(d_a, d_b) if (1 == 0)
    {
        #pragma acc parallel present(d_a[0:n],d_b[0:n]) 
        {
            #pragma acc loop
            for(int x = 0; x < n; ++x){
                d_b[x] = d_a[x];
            }
        }
    }

    acc_copyout(b, n * sizeof(real_t));

    for(int x = 0; x < n; ++x){
        if(fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a); free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}