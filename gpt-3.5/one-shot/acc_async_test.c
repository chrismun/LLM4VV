#ifndef T1
//T1:async,V:1.0-2.0
int test1(){
    int err = 0;
    rand(); rand(); rand(); rand(); rand();
    srand(SEED);
    unsigned int * a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * b = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * c = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * d = (unsigned int *)malloc(n * sizeof(unsigned int));

    unsigned int * copy_c = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * copy_d = (unsigned int *)malloc(n * sizeof(unsigned int));

    if(!a || !b || !c || !d || !copy_c || !copy_d){
        fprintf(stderr, "Test1: Memory Allocation Failed.\n");
        return 1;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand();
        b[x] = rand();
        c[x] = 0;
        d[x] = 0;
    }

    copyin_update(n, copy_c, c);
    copyin_update(n, copy_d, d);

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n], d[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }

        #pragma acc parallel async(2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] - b[x];
            }
        }
    }

    // Making sure the data has been copied back before comparing it
#pragma acc wait(2)

    for (int x = 0; x < n; ++x){
        if ((a[x] + b[x]) != c[x]){
            err += 1;
            break;
        }

        if ((a[x] - b[x]) != d[x]){
            err += 1;
            break;
        }
    }

    if (compare_data(n, copy_c, c)){
        err += 1;
    }

    if (compare_data(n, copy_d, d)){
        err += 1;
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(copy_c);
    free(copy_d);

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