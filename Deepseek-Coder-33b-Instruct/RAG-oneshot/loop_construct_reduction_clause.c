#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int i, sum = 0;
    int a[N];

    for(i = 0; i < N; i++) {
        a[i] = i;
    }

    #pragma acc data copyin(a[0:N]) copyout(sum)
    {
        #pragma acc parallel loop reduction(+:sum)
        for(i = 0; i < N; i++) {
            sum += a[i];
        }
    }

    printf("Sum = %d\n", sum);

    return 0;
}