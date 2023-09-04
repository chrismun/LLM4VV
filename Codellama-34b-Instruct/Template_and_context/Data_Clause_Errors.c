#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Data clause with no data environment
    #pragma acc data
    {
        int a = 1;
        #pragma acc parallel
        {
            a = 2;
        }
    }

    // Data clause with no data environment and no data region
    #pragma acc data
    {
        int b = 1;
        #pragma acc parallel
        {
            b = 2;
        }
    }

    // Data clause with no data environment and no data region and no data construct
    #pragma acc data
    {
        int c = 1;
        #pragma acc parallel
        {
            c = 2;
        }
    }

    // Data clause with no data environment and no data region and no data construct and no data clause
    #pragma acc data
    {
        int d = 1;
        #pragma acc parallel
        {
            d = 2;
        }
    }

    // Data environment with no data region
    #pragma acc data
    {
        int e = 1;
        #pragma acc parallel
        {
            e = 2;
        }
    }

    // Data environment with no data region and no data construct
    #pragma acc data
    {
        int f = 1;
        #pragma acc parallel
        {
            f = 2;
        }
    }

    // Data environment with no data region and no data construct and no data clause
    #pragma acc data
    {
        int g = 1;
        #pragma acc parallel
        {
            g = 2;
        }
    }

    // Data region with no data environment
    #pragma acc data
    {
        int h = 1;
        #pragma acc parallel
        {
            h = 2;
        }
    }

    // Data region with no data environment and no data construct
    #pragma acc data
    {
        int i = 1;
        #pragma acc parallel
        {
            i = 2;
        }
    }

    // Data region with no data environment and no data construct and no data clause
    #pragma acc data
    {
        int j = 1;
        #pragma acc parallel
        {
            j = 2;
        }
    }

    // Data construct with no data environment
    #pragma acc data
    {
        int k = 1;
        #pragma acc parallel
        {
            k = 2;
        }
    }

    // Data construct with no data environment and no data region
    #pragma acc data
    {
        int l = 1;
        #pragma acc parallel
        {
            l = 2;
        }
    }

    // Data construct with no data environment and no data region and no data clause
    #pragma acc data
    {
        int m = 1;
        #pragma acc parallel
        {
            m = 2;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}