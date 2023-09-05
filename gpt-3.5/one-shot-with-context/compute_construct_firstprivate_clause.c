#include "acc_testsuite.h"
bool firstpriv_2514() {
    srand(SEED);
    int host_err = 0;
    const int total = 100000;
    int* a = (int*)malloc(sizeof(int) * total);
    int* b = (int*)malloc(sizeof(int) * total);
    int* c = (int*)malloc(sizeof(int) * total);
    int* d = (int*)malloc(sizeof(int) * total);
    int* f = (int*)malloc(sizeof(int) * total);
    int* g = (int*)malloc(sizeof(int) * total);
    int* h = (int*)malloc(sizeof(int) * total);
    int* i = (int*)malloc(sizeof(int) * total);
    int* j = (int*)malloc(sizeof(int) * total);
    int* k = (int*)malloc(sizeof(int) * total);
    int* l = (int*)malloc(sizeof(int) * total);
    int* m = (int*)malloc(sizeof(int) * total);
    int* n = (int*)malloc(sizeof(int) * total);
    int* o = (int*)malloc(sizeof(int) * total);
    int* p = (int*)malloc(sizeof(int) * total);
    int* q = (int*)malloc(sizeof(int) * total);
    int* r = (int*)malloc(sizeof(int) * total);
    int* w = (int*)malloc(sizeof(int) * total);
    int* x = (int*)malloc(sizeof(int) * total);
    int* y = (int*)malloc(sizeof(int) * total);
    int* z = (int*)malloc(sizeof(int) * total);

    for (int j = 0; j < total; ++j){
        a[j] = 1;
        b[j] = j;
        c[j] = 2;
        d[j] = 3;
        f[j] = 4;
        g[j] = 5;
        h[j] = 6;
        i[j] = 7;
        k[j] = 8;
        l[j] = 9;
        m[j] = 10;
        n[j] = 11;
        o[j] = 12;
        p[j] = 13;
        q[j] = 14;
        r[j] = 15;
        w[j] = 16;
        x[j] = 17;
        y[j] = 18;
        z[j] = 19;
    }
    #pragma acc data copyin(a[0:total], b[0:total], c[0:total], d[0:total], f[0:total], g[0:total], h[0:total], i[0:total], k[0:total], l[0:total], m[0:total], n[0:total], o[0:total], p[0:total], q[0:total], r[0:total], w[0:total], x[0:total], y[0:total], z[0:total])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (int j = 0; j < total; ++j){
                a[j] += b[j] + c[j] + d[j] + f[j] + g[j] + h[j] + i[j] + k[j] + l[j] + m[j] + n[j] + p[j] + q[j] + r[j] + w[j] + x[j] + y[j] + z[j];
            }
        }
    }
    for (int j = 1; j < total; ++j){
        if(a[j] != a[j - 1] + 1 + b[j] + c[j] + d[j] + f[j] + g[j] + h[j] + i[j] + k[j] + l[j] + m[j] + n[j] + p[j] + q[j] + r[j] + w[j] + x[j] + y[j] + z[j]){
            host_err++;
        }
    }
    return host_err == 0;
}

int main() {
    if (!firstpriv_2514()) {
        printf("Test failed\n");
    }
    return 0;