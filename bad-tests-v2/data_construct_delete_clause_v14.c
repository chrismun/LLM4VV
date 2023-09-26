#ifndef T1
//T1:construct-independent,executable-region,serial,data,data-region,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        while (a[x] == 0){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
        }
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data delete(a[0:n]) copyout(a[0:n])
    {
        //We have tested that we can get a buffer here by using acc_map_data.
        //So that means at this point we have a slew of references to this buffer.
        //Hell, we even open data regions that reference this, so we can't delete the buffer here.
        //At the end of the construct, we should be able to delete the buffer without any problems though.
        real_t * b = (real_t *)malloc(n * sizeof(real_t));
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }

        #pragma acc data delete(a[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] += b[x];
            }
        }
        #pragma acc data delete(b[0:n])
        #pragma acc data copyout(b[0:n])
        {
            for (int x = 0; x < n; ++x){
                b[x] += a[x];
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(b[x] - 2 * a[x]) > PRECISION){
                err = 1;
            }
        }
    }
    #pragma acc exit data delete(a[0:n])

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