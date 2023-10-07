#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int m = 100;
    int tile_size = 10;
    int tile_size_2 = 10;
    int tile_size_3 = 10;
    int tile_size_4 = 10;
    int tile_size_5 = 10;
    int tile_size_6 = 10;
    int tile_size_7 = 10;
    int tile_size_8 = 10;
    int tile_size_9 = 10;
    int tile_size_10 = 10;

    int* a = (int*)malloc(n * m * sizeof(int));
    int* b = (int*)malloc(n * m * sizeof(int));
    int* c = (int*)malloc(n * m * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i * m + j] = i * j;
            b[i * m + j] = i * j;
            c[i * m + j] = i * j;
        }
    }

    #pragma acc parallel loop tile(tile_size, tile_size_2, tile_size_3, tile_size_4, tile_size_5, tile_size_6, tile_size_7, tile_size_8, tile_size_9, tile_size_10)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i * m + j] += b[i * m + j];
            c[i * m + j] += b[i * m + j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i * m + j] != c[i * m + j]) {
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);
    free(c);

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