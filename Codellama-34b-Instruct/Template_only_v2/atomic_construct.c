#include "acc_testsuite.h"
#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc atomic
    {
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int g = 0;
        int h = 0;
        int i = 0;
        int j = 0;
        int k = 0;
        int l = 0;
        int m = 0;
        int n = 0;
        int o = 0;
        int p = 0;
        int q = 0;
        int r = 0;
        int s = 0;
        int t = 0;
        int u = 0;
        int v = 0;
        int w = 0;
        int x = 0;
        int y = 0;
        int z = 0;

        #pragma acc atomic
        {
            a = 1;
            b = 2;
            c = 3;
            d = 4;
            e = 5;
            f = 6;
            g = 7;
            h = 8;
            i = 9;
            j = 10;
            k = 11;
            l = 12;
            m = 13;
            n = 14;
            o = 15;
            p = 16;
            q = 17;
            r = 18;
            s = 19;
            t = 20;
            u = 21;
            v = 22;
            w = 23;
            x = 24;
            y = 25;
            z = 26;
        }

        #pragma acc atomic
        {
            a = a + 1;
            b = b + 2;
            c = c + 3;
            d = d + 4;
            e = e + 5;
            f = f + 6;
            g = g + 7;
            h = h + 8;
            i = i + 9;
            j = j + 10;
            k = k + 11;
            l = l + 12;
            m = m + 13;
            n = n + 14;
            o = o + 15;
            p = p + 16;
            q = q + 17;
            r = r + 18;
            s = s + 19;
            t = t + 20;
            u = u + 21;
            v = v + 22;
            w = w + 23;
            x = x + 24;
            y = y + 25;
            z = z + 26;
        }

        #pragma acc atomic
        {
            a = a + 1;
            b = b + 2;
            c = c + 3;
            d = d + 4;
            e = e + 5;
            f = f + 6;
            g = g + 7;
            h = h + 8;
            i = i + 9;
            j = j + 10;
            k = k + 11;
            l = l + 12;
            m = m + 13;
            n = n + 14;
            o = o + 15;
            p = p + 16;
            q = q + 17;
            r = r + 18;
            s = s + 19;
            t = t + 20;
            u = u + 21;
            v = v + 22;
            w = w + 23;
            x = x + 24;
            y = y + 25;
            z = z + 26;
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