#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct,self,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict f = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict g = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict h = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict i = (real_t *)malloc(n * sizeof(real_t));
        real_t * restrict total = (real_t *)malloc(10 * n * sizeof(real_t));
        real_t * restrict host_total = (real_t *)malloc(50 * n * sizeof(real_t));
        int found = 0;
        int found_host = 0;

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = rand() / (real_t)(RAND_MAX / 10);
            d[x] = 1;
            e[x] = rand() / (real_t)(RAND_MAX / 10);
            f[x] = rand() / (real_t)(RAND_MAX / 10);
            g[x] = rand() / (real_t)(RAND_MAX / 10);
            h[x] = 1;
            i[x] = rand() / (real_t)(RAND_MAX / 10);
        }
        for (int x = 0; x < 10 * n; ++x) {
            total[x] = 0;
            host_total[x] = 0;
        }

        #pragma acc data copyin(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n], f[0:n], g[0:n], h[0:n], i[0:n], total[0:10*n], n)
        {
            #pragma acc parallel self(total[0:10*n])
            {
                #pragma acc loop gang
                for (int x = 0; x < 5; ++x){
                    for (int y = 0; y < 2; ++y){
                        for (int z = 0; z < n; ++z){
                            total[x * 2 * n + y * n + z] = a[z] + b[z] + c[z] + d[z];
                        }
                    }
                }
                #pragma acc loop gang
                for (int x = 0; x < 5; ++x){
                    for (int y = 0; y < 2; ++y){
                        for (int w = 0; w < n; ++w){
                            total[10 * n - 1 - (x * 2 * n + y * n + w)] = e[w] + f[w] + g[w] + h[w];
                        }
                    }
                }
            }
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 10; ++y){
                    host_total[x * 10 + y] = a[x] + b[x] + c[x] + d[x] + e[x] + f[x] + g[x] + h[x];
                }
            }
        }

        for (int x = 0; x < 10 * n; ++x){
            if (fabs(host_total[x] - total[x]) > n * PRECISION){
                err += 1;
                break;
            }
        }
        for (int x = 0; x < 5; ++x){
            for (int y = 0; y < 2; ++y){
                for (int z = 0; z < n; ++z){
                    if (fabs(total[x * 2 * n + y * n + z] - (a[z] + b[z] + c[z] + d[z]))) > PRECISION{
                        err += 1;
                        break;
                    }
                }
            }
        }
        for (int x = 0; x < 5; ++x){
            for (int y = 0; y < 2; ++y){
                for (int z = 0; z < n; ++z){
                    if (fabs(total[10 * n - 1 - (x * 2 * n + y * n + z)] - (e[z] + f[z] + g[z] + h[z]))) > n * PRECISION){
                        err += 1;
                        break;
                    }
                }
            }
        }

        for (int x = 0; x < n; ++x){
            for (int y = 0; y < 8; ++y){
                i[x] += total[y * n + x];
            }
        }
        for (int x = 0; x < n; ++x){
            if (fabs(i[x] - 8 * (1 + a[x] + b[x] + c[x] + d[x]))) < n * PRECISION{
                err = 1;
            }
        }

        free(a);
        free(b);
        free(c);
        free(d);
        free(e);
        free(f);
        free(g);
        free(h);
        free(i);
        free(total);
        free(host_total);
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