#ifndef T1
//T1:async,wait,devonly,V:2.5-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data copyout(b[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] / 2;
            }
        }
        acc_async_test(1);
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }


    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x]/2)) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2

int test2(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * b = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * 10* sizeof(real_t));
    acc_copyin(a, n * 10 * sizeof(real_t));
    acc_copyin(b, n * 10 * sizeof(real_t));

    for (int x = 0; x < n * 10; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_host[x] = a[x];
        b[x] = x;
        b_host[x] = b[x];
    }

#pragma acc data present(a[0:n*10])
    {
        #pragma acc parallel loop async(1) gang collapse(1)
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < n; ++y) {
                a[x * n + y] = a[x * n + y] / 2;
            }
        }
        acc_async_test(1);
#pragma acc parallel loop gang collapse(1)
        for (int x = 1; x < 10; ++x) {
            for (int y = 0; y < n; ++y) {
                b[x * n + y] = a[x * n + y];
            }
        }
    }

    for (int x = 0; x < n * 10; ++x) {
        if (fabs(b_host[x] - x) > PRECISION) {
            err += 1;
            break;
        }
    }

    acc_copyout(a, n * 10 * sizeof(real_t));
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (fabs(a_host[x * 10 + y] - a[x * 10 + y] * 2) > PRECISION) {
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:async,wait,devonly,V:2.5-2.7
int test3(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * b = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * c = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * 10* sizeof(real_t));
    real_t * c_host = (real_t *)malloc(n * 10* sizeof(real_t));
    acc_copyin(a, n * 10 * sizeof(real_t));
    acc_copyin(b, n * 10 * sizeof(real_t));
    acc_copyin(c, n * 10 * sizeof(real_t));

    for (int x = 0; x < n * 10; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_host[x] = a[x];
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = b[x];
        c[x] = 0;
        c_host[x] = 0;
    }

    #pragma acc data present(a[0:n*10], b[0:n*10], c[0:n*10])
    {
        #pragma acc parallel loop async (1) collapse (1)
        for (int x = 0; x < n; x++){
            a[x] *= a[x];
        }
        #pragma acc parallel loop async (2) collapse (1)
        for (int x = 0; x < n; x++){
            b[x] *= b[x];
        }
        acc_async_test(1);
        #pragma acc parallel loop async (1) collapse (1)
        for (int x = 0; x < n; x++){
            c[x] += a[x];
        }
        #pragma acc parallel loop async (2) collapse (1)
        for (int x = 0; x < n; x++){
            c[x] += b[x];
        }
    }

    acc_copyout(a, n * 10 * sizeof(real_t));
    acc_copyout(b, n * 10 * sizeof(real_t));
    acc_copyout(c, n * 10 * sizeof(real_t));


    for(int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(c_host[x * n + y] - (a_host[x * n + y] + b_host[x * n + y])) > PRECISION * 2){
                err += 1;
            }
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
        failed += test1();
    }
    if (failed){
        failcode += (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed){
        failcode += (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test3();
    }
    if (failed){
        failcode += (1 << 2);
    }
#endif
    return failcode;
}