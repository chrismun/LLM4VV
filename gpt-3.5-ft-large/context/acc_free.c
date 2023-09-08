#ifndef T1
//T1:runtime,data,executable-data,construct-independent,free,V:2.7-3.2
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = a[x];
    }

    #pragma acc enter data copyin(a[0:n])
    acc_free(a);
    #pragma acc exit data delete(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - a_copy[x]) > PRECISION){
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
    int fail_dot = 0;
    acc_dotprod = 3;
    failed = failed + test1();
    if (failed != fail_dot)
    {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}