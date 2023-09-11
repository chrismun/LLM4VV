#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc serial default(none)
    {
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;
        int e = 5;
        int f = 6;
        int g = 7;
        int h = 8;
        int i = 9;
        int j = 10;
        int k = 11;
        int l = 12;
        int m = 13;
        int n = 14;
        int o = 15;
        int p = 16;
        int q = 17;
        int r = 18;
        int s = 19;
        int t = 20;
        int u = 21;
        int v = 22;
        int w = 23;
        int x = 24;
        int y = 25;
        int z = 26;

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += a[i];
            }
            printf("Sum of a: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += b[i];
            }
            printf("Sum of b: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += c[i];
            }
            printf("Sum of c: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += d[i];
            }
            printf("Sum of d: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += e[i];
            }
            printf("Sum of e: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += f[i];
            }
            printf("Sum of f: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += g[i];
            }
            printf("Sum of g: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += h[i];
            }
            printf("Sum of h: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += i[i];
            }
            printf("Sum of i: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += j[i];
            }
            printf("Sum of j: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += k[i];
            }
            printf("Sum of k: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += l[i];
            }
            printf("Sum of l: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += m[i];
            }
            printf("Sum of m: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += n[i];
            }
            printf("Sum of n: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += o[i];
            }
            printf("Sum of o: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += p[i];
            }
            printf("Sum of p: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += q[i];
            }
            printf("Sum of q: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += r[i];
            }
            printf("Sum of r: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += s[i];
            }
            printf("Sum of s: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += t[i];
            }
            printf("Sum of t: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += u[i];
            }
            printf("Sum of u: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += v[i];
            }
            printf("Sum of v: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += w[i];
            }
            printf("Sum of w: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += x[i];
            }
            printf("Sum of x: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += y[i];
            }
            printf("Sum of y: %d\n", sum);
        }

        #pragma acc parallel
        {
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                sum += z[i];
            }
            printf("Sum of z: %d\n", sum);
        }
    }

    return 0;
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