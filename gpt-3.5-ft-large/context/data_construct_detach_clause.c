#ifndef T1
//T1: data,data-constructs,enter-data,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));
    real_t * h = (real_t *)malloc(n * sizeof(real_t));
    real_t * i = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
        g[x] = 1.0;
        h[x] = rand() / (real_t)(RAND_MAX / 10);
        i[x] = 0.0;
    }
    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n], h[0:n], g[0:n]) present(c[0:n], f[0:n], i[0:n])
    {
        #pragma acc enter data deviceptr(devtest) copyin(devtest[0:1])
        #pragma acc parallel
        {
            devtest[0] = 1;
        }
        #pragma acc exit data delete(c[:n]) detach(c[0:n])
        #pragma acc exit data delete(f[:n]) detach(f[0:n]) finalize(test1_finalize: f[0:n])
        #pragma acc exit data delete(i[:n]) finalize(test1_finalize_if_0: if(devtest[0] == 0) i[0:n]) finalize(test1_finalize_if_1: if(devtest[0] == 1) i[0:n]))
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    f[x] = d[x] + e[x];
                }
            }
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    i[x] = h[x] * 2;
                }
            }
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > (2 * PRECISION)){
            err += 1;
        }
        if (fabs(f[x] - (d[x] + e[x])) > (2 * PRECISION)){
            err += 1;
        }
        if (fabs(i[x] - (h[x] * 2)) > (2 * PRECISION)){
            err += 1;
        }
    }
    for (int x = 0; x < n; ++x){
        if (devtest[0] == 1){
            if (fabs(i[x]) < 2 * PRECISION){
                err++;
            }
        }
        else {
            if (fabs(i[x] - (h[x] * 2)) > PRECISION){
                err++;
            }
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n], d[0:n], e[0:n], h[0:n])
    return err;
}
void test1_finalize(real_t * f, int * passed){
    for (int x = 0; x < n; ++x){
        if (fabs(f[x] - (f[x] + PRECISION/2))) > PRECISION){
	           passed[0] = 1;
	      }
    }
}
void test1_finalize_if_1(real_t * f, int * passed){
    for (int x = 0; x < n; ++x){
        if (fabs(f[x] - (2 * (f[x] + PRECISION/2)))) > PRECISION){
	           passed[0] = 1;
	      }
    }
}

void test1_finalize_if_0(real_t * f, int * passed){
    for (int x = 0; x < n; ++x){
        if (fabs(f[x] - (f[x] + PRECISION/4))) > PRECISION){
	           passed[0] = 1;
	      }
    }
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