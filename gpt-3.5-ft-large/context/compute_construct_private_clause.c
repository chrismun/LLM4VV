#include "acc_testsuite.h"
#ifndef T1
//T1:private,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * minimum = (real_t *)malloc(10 * sizeof(real_t));
    real_t temp = 0.0;
    int init_0 = 1;
    int init_1 = 1;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }
    for (int x = 0; x < 10; ++x){
        minimum[x] = 1000;
    }
    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            #pragma acc loop private(minimum)
            for (int x = 0; x < n; ++x){
                if (c[x] <  minimum[x%10]){
                    minimum[x%10] = c[x];
                }
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                if (fabs(c[x] - minimum[x%10]) > PRECISION){
                    init_0 = 0;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            init_1 = 0;
        }
    }

    for (int x = 0; x < 10; ++x){
        temp = 0;
        for (int y = 0; y < n/10; ++y){
            if (temp > (a[x * n/10 + y] + b[x * n/10 + y])){
                temp = a[x * n/10 + y] + b[x * n/10 + y];
            }
        }
        if (fabs(minimum[x]) > PRECISION && fabs(temp) > PRECISION) {
            continue;
        }
        if (fabs(minimum[x] - temp) > PRECISION){
            err += 1;
        }
    }
    if (err > init_0 + init_1){
        return 1;
    }
    return 0;