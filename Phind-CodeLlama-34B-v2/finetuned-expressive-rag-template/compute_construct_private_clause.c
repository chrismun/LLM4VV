#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p, *q, *r, *s, *t, *u, *v, *w, *x, *y, *z;
    int num_elements = 1024;

    a = (int *)malloc(num_elements * sizeof(int));
    b = (int *)malloc(num_elements * sizeof(int));
    c = (int *)malloc(num_elements * sizeof(int));
    d = (int *)malloc(num_elements * sizeof(int));
    e = (int *)malloc(num_elements * sizeof(int));
    f = (int *)malloc(num_elements * sizeof(int));
    g = (int *)malloc(num_elements * sizeof(int));
    h = (int *)malloc(num_elements * sizeof(int));
    i = (int *)malloc(num_elements * sizeof(int));
    j = (int *)malloc(num_elements * sizeof(int));
    k = (int *)malloc(num_elements * sizeof(int));
    l = (int *)malloc(num_elements * sizeof(int));
    m = (int *)malloc(num_elements * sizeof(int));
    n = (int *)malloc(num_elements * sizeof(int));
    o = (int *)malloc(num_elements * sizeof(int));
    p = (int *)malloc(num_elements * sizeof(int));
    q = (int *)malloc(num_elements * sizeof(int));
    r = (int *)malloc(num_elements * sizeof(int));
    s = (int *)malloc(num_elements * sizeof(int));
    t = (int *)malloc(num_elements * sizeof(int));
    u = (int *)malloc(num_elements * sizeof(int));
    v = (int *)malloc(num_elements * sizeof(int));
    w = (int *)malloc(num_elements * sizeof(int));
    x = (int *)malloc(num_elements * sizeof(int));
    y = (int *)malloc(num_elements * sizeof(int));
    z = (int *)malloc(num_elements * sizeof(int));

    for (int x = 0; x < num_elements; ++x){
        a[x] = rand() % num_elements;
        b[x] = rand() % num_elements;
        c[x] = rand() % num_elements;
        d[x] = rand() % num_elements;
        e[x] = rand() % num_elements;
        f[x] = rand() % num_elements;
        g[x] = rand() % num_elements;
        h[x] = rand() % num_elements;
        i[x] = rand() % num_elements;
        j[x] = rand() % num_elements;
        k[x] = rand() % num_elements;
        l[x] = rand() % num_elements;
        m[x] = rand() % num_elements;
        n[x] = rand() % num_elements;
        o[x] = rand() % num_elements;
        p[x] = rand() % num_elements;
        q[x] = rand() % num_elements;
        r[x] = rand() % num_elements;
        s[x] = rand() % num_elements;
        t[x] = rand() % num_elements;
        u[x] = rand() % num_elements;
        v[x] = rand() % num_elements;
        w[x] = rand() % num_elements;
        x[x] = rand() % num_elements;
        y[x] = rand() % num_elements;
        z[x] = rand() % num_elements;
    }

    #pragma acc data copy(a[0:num_elements], b[0:num_elements], c[0:num_elements], d[0:num_elements], e[0:num_elements], f[0:num_elements], g[0:num_elements], h[0:num_elements], i[0:num_elements], j[0:num_elements], k[0:num_elements], l[0:num_elements], m[0:num_elements], n[0:num_elements], o[0:num_elements], p[0:num_elements], q[0:num_elements], r[0:num_elements], s[0:num_elements], t[0:num_elements], u[0:num_elements], v[0:num_elements], w[0:num_elements], x[0:num_elements], y[0:num_elements], z[0:num_elements])
    {
        #pragma acc parallel private(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)
        {
            #pragma acc loop
            for (int x = 0; x < num_elements; ++x){
                a[x] = b[x] + c[x] + d[x] + e[x] + f[x] + g[x] + h[x] + i[x] + j[x] + k[x] + l[x] + m[x] + n[x] + o[x] + p[x] + q[x] + r[x] + s[x] + t[x] + u[x] + v[x] + w[x] + x[x] + y[x] + z[x];
            }
        }
    }

    for (int x = 0; x < num_elements; ++x){
        if (a[x] != (b[x] + c[x] + d[x] + e[x] + f[x] + g[x] + h[x] + i[x] + j[x] + k[x] + l[x] + m[x] + n[x] + o[x] + p[x] + q[x] + r[x] + s[x] + t[x] + u[x] + v[x] + w[x] + x[x] + y[x] + z[x])){
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
    free(j);
    free(k);
    free(l);
    free(m);
    free(n);
    free(o);
    free(p);
    free(q);
    free(r);
    free(s);
    free(t);
    free(u);
    free(v);
    free(w);
    free(x);
    free(y);
    free(z);

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