#include <stdio.h>
#include <openacc.h>

int main()
{
    int n = 10;
    int a = 5;
    int b[n];

    #pragma acc parallel loop firstprivate(a)
    for(int i=0; i<n; ++i){
        b[i] = a * i;
        a++; // this will not affect the 'a' outside of this construct
    }

    printf("Outside of the construct, a = %d\n", a);
    for(int i=0; i<n; ++i){
        printf("b[%d] == %d\n", i, b[i]);
    }

    return 0;
}