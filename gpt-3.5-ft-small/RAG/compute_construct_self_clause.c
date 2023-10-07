#ifndef T1
//T1:self,executable-data,construct-independent,runtime-outside
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * totals = (real_t *)malloc(devnum * sizeof(real_t));

    for (int x = 0; x < devnum; ++x){
        totals[x] = 0;
        #pragma acc enter data copyin(totals[x:1])
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data present(a[0:n], b[0:n]) create(totals[0:devnum])
    {
        for (int x = 0; x < devnum; ++x){
            #pragma acc loop seq
            for (int y = 0; y < n; ++y){
                totals[x] += (a[y] * b[y])/(rand() / (real_t)RAND_MAX + 1);
            }
        }
    }

    for (int x = 0; x < devnum; ++x){
        #pragma acc exit data copyout(totals[x:1])
    }

    for (int x = 0; x < devnum; ++x){
        #pragma acc parallel present(totals[x:1]) num_gangs(1) vector_length(1)
        {
            #pragma acc loop seq
            for (int y = 0; y < 1; ++y){
                #pragma acc loop worker
                for (int z = 0; z < x; ++z){
                    totals[x] += totals[z];
                }
            }
        }
    }

    #pragma acc parallel
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            #pragma acc atomic            
                c[x] += a[x] * b[x];
        }
    }
    #pragma acc wait
  
    int no_fault = 1;
    for (int x = 0; x < devnum; ++x){
        for (int y = x; y <= devnum; ++y){
            real_t temp = 0;
            for (int z = x; z < y; ++z){
                temp += totals[z];
            }
            if (fabs(temp - c[0]) > PRECISION){
                no_fault = 0;
            }
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - ((a[x] * b[x]) * ((devnum * (devnum + 1)) / 2))) > PRECISION){
            err = 1;
        }
    }
    if (no_fault == 0){
        err += 10;
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
    return failcode;
}