#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 10;
    int m = 10;
    int p = 10;
    int q = 10;
    int r = 10;
    int s = 10;
    int t = 10;
    int u = 10;
    int v = 10;
    int w = 10;
    int x = 10;
    int y = 10;
    int z = 10;

    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                for (int l = 0; l < q; l++) {
                    for (int m = 0; m < r; m++) {
                        for (int n = 0; n < s; n++) {
                            for (int o = 0; o < t; o++) {
                                for (int p = 0; p < u; p++) {
                                    for (int q = 0; q < v; q++) {
                                        for (int r = 0; r < w; r++) {
                                            for (int s = 0; s < x; s++) {
                                                for (int t = 0; t < y; t++) {
                                                    for (int u = 0; u < z; u++) {
                                                        // Do something
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
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