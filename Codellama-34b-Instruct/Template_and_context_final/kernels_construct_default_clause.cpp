#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc kernels default(none)
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