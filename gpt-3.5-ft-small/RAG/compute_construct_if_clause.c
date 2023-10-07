#ifndef T1
//T1:comp:kernels,loop,if,combined-constructs,parallel,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * cond = (int *)malloc((n/256+1) * sizeof(int));
    real_t temp = 0.0;

    for (int x = 0; x < n; ++x){
        cond[(int)(x/256)] = 1;
        c[x] = 3;
        a[x] = 1;
        b[x] = 1;
    }

    #pragma acc data copyin(cond[0:n/256+1]) copy(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel present(cond[0:n/256+1])
        {
            #pragma acc loop
            for (int x = 0; x < n/256+1; ++x){
                if (cond[x] == 0) {
                    cond[x] = 1;
                    #pragma acc atomic capture
                        cond[x] = 0;
                }
            }
        }
        #pragma acc kernels loop gang worker independent present(a[0:n], b[0:n], cond[0:n/256+1])
        for (int x = 0; x < n; ++x){
            if (cond[(int)(x/256)] == 1) {
                #pragma acc loop seq
                for (int y = 0; y < 10; ++y){
                    temp = 0;
                    for (int z = 0; z < x; ++z){
                        temp += a[z] + b[z];
                    }
                    c[x] += temp * y;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (cond[(int)(x/256)] == 0){
            for (int y = 0; y < 10; ++y){
                temp = 0;
                for (int z = 0; z < x; ++z){
                    temp += a[z] + b[z];
                }
                c[x] += temp * y;
            }
        }
        else if (cond[(int)(x/256)] != 1 && (c[x] != 1 + (real_t)10 * ((x / 256) * ((x / 256) + 1)) / 2 * 256)){
            err += 1;
            if (DEBUGMODE){
                printf("%d -- %d != 1 + 10 * %d * %d\n", x, c[x], x / 256, (x / 256) + 1);
            }
        }
        else if (cond[(int)(x/256)] == 1 && (c[x] != 3 + 10 * ( (real_t)(x % 256) * ((x % 256) + 1)) / 2)){
            err += 1;
            if (DEBUGMODE){
                printf("%d -- %d != 3 + 10 * %d * %d\n", x, c[x], x / 256, (x / 256) + 1);
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
    return failcode;
}