#include "acc_testsuite.h"
#ifndef T1
//T1:detach,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *totals = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    for (int x = 0; x < 10; ++x){
        totals[x] = -1;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(totals[0:10])
    {
        #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) present(a[0:n], b[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] = 2 + a[x];
                b[x] = -1 * b[x];
            }
        }

        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                totals[0] += a[x] + b[x];
            }
        }
    }
    totals[0] = 0;
    for (int x = 0; x < n; ++x){
        totals[0] += 2 + a[x] - (-1) * b[x];
    }
    for (int x = 0; x < 10; ++x){
        if (fabs(totals[0] - totals[x]) > PRECISION * (2 + fabs(totals[0]))){
            err += 1;
            break;
        }
    }
    
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t) RAND_MAX;
        b[x] = rand() / (real_t) RAND_MAX;
    }
    totals[0] = -1;
    totals[1] = -1;
    
    #pragma acc enter data create(a[0:n], b[0:n]) copyin(totals[0:2])
    for (int x = 0; x < 512; ++x){
        #pragma acc parallel present(a[0:n], b[0:n]) num_gangs(ceil((n + 1) / 512)) vector_length(512)
        {
            #pragma acc loop gang
            for (int y = 0; y < ceil((n + 1) / 512); ++y){
                #pragma acc loop vector
                for (int z = 0; z < 512; ++z){
                    if ((z + y * 512) < n){
                        a[z + y * 512] = z + y * 512 + 1;
                        b[z + y * 512] = (z + y * 512) / 2.0;
                    }
                }
            }
        }
    }

    for (int x = 0; x < 16; ++x){
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                a[y] = a[y] + b[y];
                b[y] = a[y] - b[y];
                a[y] = a[y] - b[y];
            }
        }
    }

    #pragma acc exit data copyout(a[0:n])
    totals[0] = 0;
    for (int x = 0; x < 512; ++x){
        totals[0] += x + 1;
    }
    totals[0] = totals[0] * 512;
    totals[1] = 0;
    for (int x = 0; x < n % 512; ++x){
        totals[1] += x + 1 + 512 * (n / 512);
    }
    #pragma acc exit data copyin(totals[0:2])
    #pragma acc data copyin(a[0:n])
    {
        for (int x = 0; x < 512; ++x){
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < ceil((n + 1) / 512); ++y){
                    if ((x * 512 + y * 512) < n)
                        totals[1] += a[x * 512 + y * 512];
                }
            }
        }
    }

    if (fabs(totals[0] - totals[1]) > n * PRECISION * (512 * (n / 512) + ceil((n + 1) / 512)) + PRECISION * (2 + fabs(totals[0]))){
        err += 1;
    }
    if (err == 0){
        return 0;