#ifndef T1
//T1:parallel,combined-constructs,loop,combined-constructs,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int *a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *b = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *tot;
    unsigned int temp = 0;

    for (unsigned int x = 0; x < n; ++x){
        a[x] = (unsigned int) rand() / (real_t) (rand() + 1);
        b[x] = (unsigned int) rand() / (real_t) (rand() + 1);
    }
    #pragma acc data copyin(a[0:n], b[0:n]) copy(tot[0:n])
    {
        #pragma acc parallel loop private(temp) reduction(+:tot)
        for (unsigned int x = 0; x < n; ++x){
            temp = 1;
            for (unsigned int y = 0; y < x; ++y){
                temp += a[x] * b[y];
            }
            tot[x] = temp;
        }
    }

    for (unsigned int x = 0; x < n; ++x){
        temp = 1;
        for (unsigned int y = 0; y < x; ++y){
            temp += a[x] * b[y];
        }
        if (temp != tot[x]){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}