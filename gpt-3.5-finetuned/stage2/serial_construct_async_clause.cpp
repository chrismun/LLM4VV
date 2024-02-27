#include "acc_testsuite.h"
#ifndef T1
//T1:serial,async,construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int device_type = acc_get_device_type();
    if (device_type != acc_device_none){
        real_t *a = new real_t[1000];
        real_t *b = new real_t[1000];
        real_t *c = new real_t[1000];
        real_t *d = new real_t[1000];
        real_t *e = new real_t[1000];
        real_t *f = new real_t[1000];
        real_t *g = new real_t[1000];
        real_t *h = new real_t[1000];
        real_t *i = new real_t[1000];
        real_t *a_host = new real_t[1000];
        real_t *b_host = new real_t[1000];
        real_t *c_host = new real_t[1000];
        real_t *d_host = new real_t[1000];
        real_t *e_host = new real_t[1000];
        real_t *f_host = new real_t[1000];
        real_t *g_host = new real_t[1000];
        real_t *h_host = new real_t[1000];
        real_t *i_host = new real_t[1000];

        for (int x = 0; x < 1000; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
            d[x] = rand() / (real_t)(RAND_MAX / 10);
            e[x] = rand() / (real_t)(RAND_MAX / 10);
            f[x] = 0;
            g[x] = rand() / (real_t)(RAND_MAX / 10);
            h[x] = 0;
            i[x] = 0;
            a_host[x] = a[x];
            b_host[x] = b[x];
            c_host[x] = 0;
            d_host[x] = d[x];
            e_host[x] = e[x];
            f_host[x] = 0;
            g_host[x] = g[x];
            h_host[x] = 0;
            i_host[x] = 0;
        }

        #pragma acc data copyin(a[0:1000], b[0:1000], d[0:1000], e[0:1000], g[0:1000]) create(c[0:1000], f[0:1000], h[0:1000]) copyout(i[0:1000])
        {
            #pragma acc serial async(1)
            {
                #pragma acc loop
                for (int x = 0; x < 1000; ++x){
                    c[x] = a[x] + b[x];
                }
            }
            #pragma acc serial async(2)
            {
                #pragma acc loop
                for (int x = 0; x < 1000; ++x){
                    f[x] = d[x] + e[x];
                }
            }
            #pragma acc serial async(3)
            {
                #pragma acc loop
                for (int x = 0; x < 1000; ++x){
                    h[x] = g[x];
                }
            }

            #pragma acc wait
            #pragma acc serial async(1) wait(2, 3)
            {
                #pragma acc loop
                for (int x = 0; x < 1000; ++x){
                    i[x] = c[x] + f[x] + h[x];
                }
            }
            #pragma acc wait(1)
        }

        for (int x = 0; x < 1000; ++x){
            if (fabs(c_host[x] - (a[x] + b[x])) > PRECISION){
                err += 1;
            }
            if (fabs(f_host[x] - (d[x] + e[x])) > PRECISION){
                err += 1;
            }
            if (fabs(h_host[x] - g[x]) > PRECISION){
                err += 1;
            }
            if (fabs(i_host[x] - (c_host[x] + f_host[x] + h_host[x])) > PRECISION){
                err += 1;
            }
        }

        delete[] a;
        delete[] b;
        delete[] c;
        delete[] d;
        delete[] e;
        delete[] f;
        delete[] g;
        delete[] h;
        delete[] i;
        delete[] a_host;
        delete[] b_host;
        delete[] c_host;
        delete[] d_host;
        delete[] e_host;
        delete[] f_host;
        delete[] g_host;
        delete[] h_host;
        delete[] i_host;
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