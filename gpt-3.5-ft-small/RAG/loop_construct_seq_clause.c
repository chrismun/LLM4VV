#ifndef T1
//T1:loop,seq,combined-constructs,V:3.0-3.1
int test1(){
    int err = 0;
    int i, j;
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t temp = 0.0;
    real_t temp2 = 0.0;

    for (i = 0; i < 10 * n; i++){
        a[i] = rand() / (real_t)(0x7FFFFFFF);
        b[i] = 1;
    }

    for (i = 0; i < 10; i++){
        temp = 0.0;
        temp2 = 0.0;
        for (j = 0; j < n; j++){
            temp += (a[i * n + j] * b[i * n + j]);
            temp2 += (a[i * n + j] * a[i * n + j]);
        }
        temp = sqrt(temp2) / temp;
        for (j = 0; j < n; j++){
            a[i * n + j] = temp;
        }
    }


    #pragma acc data copyin(a[0:10*n]) copy(b[0:10*n])
    {
        #pragma acc loop seq
        for (i = 0; i < 10; i++){
            temp = 0.0;
            temp2 = 0.0;
            for (j = 0; j < n; j++){
                temp += (a[i * n + j] * b[i * n + j]);
                temp2 += (a[i * n + j] * a[i * n + j]);
            }
            for (j = 0; j < n; j++){
                b[i * n + j] += temp2 / temp;
            }
        }
    }

    for (i = 0; i < 10; i++){
        temp = 0.0;
        for (j = 0; j < n; j++){
            temp += (a[i * n + j] * a[i * n + j]);
        }
        if (fabs(temp - b[i * n]) > 2 * n * PRECISION){
            err += 1;
        }
        for (j = 1; j < n; j++){
            if (fabs(b[i * n] - b[i * n + j]) > PRECISION){
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}