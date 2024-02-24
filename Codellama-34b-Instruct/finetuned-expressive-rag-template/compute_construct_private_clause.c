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
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:num_elements], b[0:num_elements]) copy(c[0:num_elements])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < num_elements; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < num_elements; ++x){
        if (c[x] != a[x] + b[x]){
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