#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

#ifndef T1
//T1:serial construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(0));

    const int N = 1000;
    int a[N], b[N], c[N];

    for(int i = 0; i < N; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; ++i){
            c[i] = a[i] + b[i];
        }

        #pragma acc wait
        for(int i = 0; i < N; ++i){
            if(c[i] != a[i] + b[i]){
                err = 1;
                break;
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
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}