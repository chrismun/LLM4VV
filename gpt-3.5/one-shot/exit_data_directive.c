#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = x;
        b[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data copyout(b[0:n])

    #pragma acc data copyout(b[0:n])
    {   
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] += a[x];
            }
        }
    }

    #pragma acc exit data delete(a[0:n])

    #pragma acc exit data copyout(b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (2 * x)) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a);
    free(b);

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