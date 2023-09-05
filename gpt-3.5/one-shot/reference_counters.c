#ifndef T1
//T1:refcounting,default,V:1.0-2.5
int test1(){
    int err = 0;

    for (int x = 0; x < 50; ++x){
        real_t * a = (real_t *)malloc(n * sizeof(real_t));
        real_t * b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i){
            a[i] = i;
            b[i] = 0.0;
        }

        #pragma acc enter data copyin(a[0:n])    // Increase refcount for a

        #pragma acc data copyout(b[0:n])          // Increase refcount for b
        {
            // Do some computations on b
            for (int i = 0; i < n; ++i){
                b[i] = 2 * a[i];
            }
        }

        #pragma acc exit data delete(a[0:n])      // Decrease refcount for a

        // Verify b
        for (int i = 0; i < n; ++i){
            if (b[i] != 2 * i){
                err++;
                break;
            }
        }

        free(a);
        free(b);
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