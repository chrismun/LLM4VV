#ifndef T1
//T1:runtime,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * m * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < m; ++y){
            a[x*m+y] = rand() / (real_t)(RAND_MAX / 10);
            b[x*m+y] = rand() / (real_t)(RAND_MAX / 10);
            c[x*m+y] = 0.0;
            d[x*m+y] = 0.0;
        }
    }

    #pragma acc enter data copyin(a[0:n*m], b[0:n*m])
    #pragma acc data present(a[0:n*m], b[0:n*m])
    {
        real_t *b_host = (real_t *)malloc(n * m * sizeof(real_t));
        #pragma acc parallel present(a[0:n*m], b[0:n*m], b_host[0:n*m])
        {
            #pragma acc loop gang private(b_host)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(b_host)
                for (int y = 0; y < m; ++y){
                    b_host[x*m+y] = b[x*m+y];
                    a[x*m+y] = 0.0;
                    b[x*m+y] = 0.0;
                }
            }
            #pragma acc loop gang
            for (int x = GANG_OFFSET; x < n; ++x){
                #pragma acc loop worker
                for (int y = WORKER_OFFSET; y < m; ++y){
                    b[x*m+y] = b[x*m+y] + b_host[x*m+y-2] + b_host[(x-2)*m+y];
                }
            }
        }
        for (int x = GANG_OFFSET; x < n; ++x){
            for (int y = WORKER_OFFSET; y < m; ++y){
                a[x*m+y] = b[x*m+y];
            }
        }
        #pragma acc update self(a[0:n*m])
        #pragma acc parallel present(a[0:n*m], c[0:n*m])
        {
            #pragma acc loop gang private(b)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(b)
                for (int y = 0; y < m; ++y){
                    b = a;
                    b[x*m+y] = 0.0;
                    c[x*m+y] = 0.0;
                }
            }
            #pragma acc loop gang
            for (int x = GANG_OFFSET; x < n; ++x){
                #pragma acc loop worker
                for (int y = WORKER_OFFSET; y < m; ++y){
                    c[x*m+y] = c[x*m+y] + b[x*m+y];
                }
            }
        }
        for (int x = GANG_OFFSET; x < n; ++x){
            for (int y = WORKER_OFFSET; y < m; ++y){
                d[x*m+y] += c[x*m+y];
            }
        }
        #pragma acc exit data copyout(d[0:n*m])
    }

    for (int x = GANG_OFFSET; x < n; ++x){
        for (int y = WORKER_OFFSET; y < m; ++y){
            if (fabs(d[x*m+y] - (3 * b[(x-2)*m+y] + 3 * b[x*m+y-2] + b[(x-2)*m+y-2])) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,construct-independent,devonly,devonly-present,V:1.0-2.7
int test2(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * m * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < m; ++y){
            a[x*m+y] = 1.0;
            d[x*m+y] = 0.0;
            e[x*m+y] = 0.0;
            f[x*m+y] = 1.0;
        }
    }

    #pragma acc enter data copyin(a[0:n*m])
    #pragma acc data present(a[0:n*m])
    {
        #pragma acc parallel present(a[0:n*m])
        {
            #pragma acc loop gang
            for (int x = GANG_OFFSET; x < n; ++x){
                #pragma acc loop worker
                for (int y = WORKER_OFFSET; y < m; ++y){
                    a[x*m+y] += y / (real_t)m;
                }
            }
        }
        #pragma acc update device(a[0:n*m])
        #pragma acc parallel present(a[0:n*m], d[0:n*m])
        {
            #pragma acc loop gang private(e)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(e)
                for (int y = 0; y < m; ++y){
                    e = a;
                    e[x*m+y] -= y / (real_t)m;
                    d[x*m+y] = e[x*m+y];
                    e[x*m+y] += 2;
                }
            }
        }
        #pragma acc update self(d[0:n*m])
        #pragma acc parallel present(a[0:n*m], d[0:n*m])
        {
            #pragma acc loop gang private(e)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(e)
                for (int y = 0; y < m; ++y){
                    e = d;
                    e[x*m+y] += 2;
                }
            }
        }
        #pragma acc enter data create(f[0:n*m])
        #pragma acc parallel present(a[0:n*m], f[0:n*m])
        {
            #pragma acc loop gang private(e)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(e)
                for (int y = 0; y < m; ++y){
                    e = d;
                    e[x*m+y] += 3;
                    f = e;
                }
            }
        }
        #pragma acc exit data copyout(f[0:n*m])
    }

    for (int x = GANG_OFFSET; x < n; ++x){
        for (int y = WORKER_OFFSET; y < m; ++y){
            if (fabs(f[x*m+y] - (10 + y / (real_t)m) - 3) > PRECISION * (10 + y / (real_t)m)){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,construct-independent,devonly,devonly-present,V:2.0-2.7
int test3(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * m * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < m; ++y){
            a[x*m+y] = 0;
            b[x*m+y] = 1;
            d[x*m+y] = 0;
            e[x*m+y] = 1;
        }
    }

    #pragma acc enter data copyin(a[0:n*m], b[0:n*m])
    #pragma acc data present(a[0:n*m], b[0:n*m])
    {
        for (int x = GANG_OFFSET; x < n; ++x){
            for (int y = WORKER_OFFSET; y < m; ++y){
                a[x*m+y] = b[x*m+y] + 1;
            }
        }
        #pragma acc update device(a[0:n*m])
        #pragma acc parallel present(a[0:n*m], b[0:n*m])
        {
            #pragma acc loop gang private(e)
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker private(e)
                for (int y = 0; y < m; ++y){
                    e = a;
                    e[x*m+y] += b[x*m+y];
                    e[x*m+y] += x;
                    d[x*m+y] = e[x*m+y];
                }
            }
        }
        #pragma acc update self(d[0:n*m])
        #pragma acc parallel present(a[0:n*m], d[0:n*m])
        {
            #pragma acc loop gang
            for (int x = GANG_OFFSET; x < n; ++x){
                #pragma acc loop worker
                for (int y = WORKER_OFFSET; y < m; ++y){
                    a[x*m+y] += b[x*m+y] + x;
                    a[x*m+y] += y;
                }
            }
        }
        #pragma acc update self(a[0:n*m])
    }

    for (int x = GANG_OFFSET; x < n; ++x){
        for (int y = WORKER_OFFSET; y < m; ++y){
            if (fabs(a[x*m+y] - (4*b[(x-2)*m+y-2] + 2 * (2 + x + (y-2) / (real_t)m)))) {
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
    for (int x = 0; x < T1_CALLS; ++x){
        failed += test1() != 0;
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < T2_CALLS; ++x){
        failed += test2() != 0;
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < T3_CALLS; ++x){
        failed += test3() != 0;
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
    return failcode;
}