#ifndef T1
//T1:parallel,set,V:2.7
int test1()
{
    int err = 0;

    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 1; // Set all elements of a to 1
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 1){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main()
{
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