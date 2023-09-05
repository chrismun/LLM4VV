#ifndef T1
//T1:data,declare,data-region,I:2711-1.0,V:1180-3.0
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc exit data delete(a[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] = 0.0;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 0.0){
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