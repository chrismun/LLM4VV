#include "acc_testsuite.h"
#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    return err;
}
#endif

#ifndef T2
struct s{
    int a[10];
    double *b;
    double *c;
};

int foo(){
    int err = 0;
    int *devtest = (int *)malloc(n * sizeof(int));
    struct s test[n];
    struct s *testptr;

    for (int x = 0; x < n; ++x){
        devtest[x] = 0;
        for (int y = 0; y < 10; ++y){
            test[x].a[y] = 1;
        }
        test[x].b = (double *)malloc(10 * sizeof(double));
        test[x].c = (double *)malloc(10 * sizeof(double));

        for (int y = 0; y < 10; ++y){
            test[x].b[y] = 1.0;
            test[x].c[y] = 0;
        }
    }

    #pragma acc data copyout(test[0:n]) create(test[0:n].b[0:10]) copy(devtest[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                devtest[x] = 1;
                #pragma acc loop
                for (int y = 0; y < 10; ++y){
                    test[x].c[y] = test[x].b[y];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (devtest[x] == 0){
            err += devtest[x];
        }
        for (int y = 0; y < 10; ++y){
            if (fabs(test[x].c[y] - test[x].b[y]) > PRECISION){
                err += 1;
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