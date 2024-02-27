#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,firstprivate,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t* a = new real_t[n];
    int * dd = (int *)malloc(2 * sizeof(int));
    int * e = (int *)malloc(2 * sizeof(int));
    std::vector<int> g;
    g.push_back(1);
    g.push_back(1);

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data firstprivate(e) copyin(g[0:1])
    {
        #pragma acc kernels firstprivate(dd)
        {
            for (int x = 0; x < n; ++x){
                dd[0] = 10;
            }
            e[0] = 1;
        }
        if (e[0] != 1){
            err += 1;
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