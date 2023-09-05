#ifndef T1
//T1:parallel,attach,reference-counting,devptr_V:2.6-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (int)(RAND_MAX / 10);
        b[x] = rand() / (int)(RAND_MAX / 10);
        c[x] = 0;
    }

    // Attach a and b to device memory
    #pragma acc data copyin(a[0:n], b[0:n]) create(c[0:n])
    {
        // First compute region
        #pragma acc parallel loop 
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }

        // Second compute region
        #pragma acc parallel loop private(c)
        for (int x = 0; x < n; ++x){
            c[x] = c[x] * 2;
        }
    }

    // Verify the result
    for (int x = 0; x < n; ++x){
        if (c[x] != (a[x]+b[x])*2){
            err += 1;
            break;
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