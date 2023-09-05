#ifndef T1
//T1:free,data,devonly,V:2.7
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));

    #pragma acc enter data copyin(a[0:n])

    #pragma acc parallel present(a)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = x;
        }
    }

    #pragma acc exit data copyout(a[0:n])

    #pragma acc enter data copyin(a[0:n])

    #pragma acc parallel present(a)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] += x;
        }
    }

    #pragma acc exit data copyout(a[0:n])

    for (int x = 0; x < n; ++x){
        if (a[x] != 2 * x){
            err += 1;
            break;
        }
    }

    free(a);

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