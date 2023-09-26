#ifndef T1
//T1:loop,loop-multiple,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * c = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * d = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * e = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * f = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * c_copy = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * d_copy = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * e_copy = (real_t *)malloc(10 * n  * sizeof(real_t));
    real_t * f_copy = (real_t *)malloc(10 * n  * sizeof(real_t));
    int i, j, d;
    real_t temp;
    int _devnum;
    int _tid = 0;
    #pragma acc data copyin(a[0:10*n], b[0:10*n], c[0:10*n], d[0:10*n], e[0:10*n], f[0:10*n]) copyout(a_copy[0:10*n], b_copy[0:10*n], c_copy[0:10*n], d_copy[0:10*n], e_copy[0:10*n], f_copy[0:10*n]) private(temp)
    {
        #pragma acc parallel num_gangs(10) num_workers(10) vector_length(32)
        {
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += a[d * n + j];
                    }
                    a_copy[i * n + j] = temp;
                }
            }
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += b[d * n + j];
                    }
                    b_copy[i * n + j] = temp;
                }
            }
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += c[d * n + j];
                    }
                    c_copy[i * n + j] = temp;
                }
            }
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += d[d * n + j];
                    }
                    d_copy[i * n + j] = temp;
                }
            }
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += e[d * n + j];
                    }
                    e_copy[i * n + j] = temp;
                }
            }
            #pragma acc loop gang
            for (i = 0; i < 10; ++i){
                #pragma acc loop worker
                for (j = 0; j < n; ++j){
                    temp = 0;
                    for (d = 0; d <= i; ++d){
                        temp += f[d * n + j];
                    }
                    f_copy[i * n + j] = temp;
                }
            }
        }
    }
    for (i = 0; i < 10; ++i){
        for (j = 0; j < n; ++j){
            for (d = 0; d < i; ++d){
                if (fabs(a_copy[i * n + j] - a_copy[d * n + j] - d * a[d * n + j]) > PRECISION){
                    err += 1;
                }
                if (fabs(b_copy[i * n + j] - b_copy[d * n + j] - d * b[d * n + j]) > PRECISION){
                    err += 1;
                }
                if (fabs(c_copy[i * n + j] - c_copy[d * n + j] - d * c[d * n + j]) > PRECISION){
                    err += 1;
                }
                if (fabs(d_copy[i * n + j] - d_copy[d * n + j] - d * d[d * n + j]) > PRECISION){
                    err += 1;
                }
                if (fabs(e_copy[i * n + j] - e_copy[d * n + j] - d * e[d * n + j]) > PRECISION){
                    err += 1;
                }
                if (fabs(f_copy[i * n + j] - f_copy[d * n + j] - d * f[d * n + j]) > PRECISION){
                    err += 1;
                }
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