#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2: loop construct auto clause combined with vector clause, V: 2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);
    int a[10 * n];
    int t1[10];
    int t2[10];

    for (int x=0; x < 10 * n; ++ x){
        a[x] = 1;
    }

    #pragma acc loop auto vector
    for (int x = 0; x < 10 * n; ++ x){
        a[x] = 2;
    }

    for (int x =0; x< 10 * n; ++x){
      if (a[x] < 2){
          t1[x%n] = 1;
      }
      else{
          t1[x%n] = 0;
      }
    }

    for (int x= 0; x< 10; ++x){
        t2[x] = 0;
    }

    #pragma acc loop auto vector
    for (int x = 0; x < 10 * n; ++x){
        t2[x % n] = t2[x % n] + t1[x % n];
    }

    for (int x = 0; x < 10; ++x){
        if (t2[x] != 1){
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

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}