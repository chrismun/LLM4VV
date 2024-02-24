#include <iostream>
#include <cmath>
#include <cstdlib>
#include <openacc.h>

#define N 100

int test1(){
    int err = 0;
    int a[N][N];
    srand(1234);

    // Initialize the array
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            a[i][j] = rand() % 100;

    // Use OpenACC to collapse the two loops
    #pragma acc parallel loop collapse(2)
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            a[i][j] = a[i][j] * 2;

    // Check the result
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(a[i][j] != rand() % 100 * 2)
                err = 1;

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}