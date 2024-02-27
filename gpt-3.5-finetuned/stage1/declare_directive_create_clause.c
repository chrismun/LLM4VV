#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t* minimum = (real_t *)malloc(10 * sizeof(real_t));
    real_t* temp_array = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t* temp_array_copy = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t* maximum = (real_t *)malloc(10 * sizeof(real_t));
    real_t* temp = (real_t *)malloc(10 * sizeof(real_t));
    real_t* iterator = (real_t *)malloc(1 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = 0;
        d[x] = 0;
    }
    for (int x = 0; x < 10; ++x){
        minimum[x] = 0;
        maximum[x] = 0;
        temp[x] = 0;
    }
    for (int x = 0; x < 100 * n; ++x){
        temp_array[x] = rand() / (real_t)(RAND_MAX / 10);
        temp_array_copy[x] = temp_array[x];
    }
    for (int x = 0; x < 10; ++x){
        iterator[x] = x;
    }

    #pragma acc data copyin(a[0:n]) create(b[0:n]) copyout(c[0:n], d[0:n]) copy(minimum[0:10], maximum[0:10], iterator[0:1], temp[0:10], temp_array[0:n*100])
    {
        #pragma acc declare create(temp_array[0:n*100])
        {
            #pragma acc parallel
            {
                real_t private_minimum[10];
                real_t private_temp[10];
                #pragma acc loop
                for (int x = 0; x < 10; ++x){
                    private_minimum[x] = 1000;
                    private_temp[x] = 0;
                }
                #pragma acc loop
                for (int x = 0; x < 100 * n; ++x){
                    temp_array[x] = a[x] * 100;
                }
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    #pragma acc loop vector reduction(min:private_temp, minimum)
                    for (int y = 0; y < 100; ++y) {
                        private_temp[y % 10] += temp_array[x * 100 + y];
                        if (y > 90){
                            minimum[y % 10] = minimum[y % 10] > temp_array[x * 100 + y] ? temp_array[x * 100 + y] : minimum[y % 10];
                        }
                    }
                    for (int y = 0; y < 10; ++y) {
                        temp[x] = private_temp[y];
                        private_temp[y] = 0;
                    }
                    for (int y = 0; y < 10; ++y) {
                        temp[x * 10 + y] = private_temp[y];
                    }
                    for (int y = 0; y < 10; ++y) {
                        private_temp[y] = 0;
                    }
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop vector reduction(+:c)
                for (int y = 0; y < 10; ++y){
                    d[x] += temp[x * 10 + y];
                    c[x] += temp[x * 10 + y] * b[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != 0){
            err += 1;
        }
        if (d[x] != c[x]){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}