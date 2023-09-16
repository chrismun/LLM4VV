#include "openacc.h"
#include <assert.h>

#define N 1000

int main() {
    int a[N], p;
    int errors = 0;

    #pragma acc data copy(a[0:N])
    {
        #pragma acc parallel loop private(p)
        for(int n = 0; n < N; n++){
            p = n;
            a[n] = p;
        }
    }

    for(int n = 0; n < N; n++){
        if(a[n] != n){
            errors++;
        }
    }

    if(errors > 0){
        printf("Test has failed with %d errors\n", errors);
        return 1;
    } else {
        printf("Test has passed successfully.\n");
        return 0;
    }
}