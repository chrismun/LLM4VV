#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    int err = 0;
    int *a, *b, *c;
    int n = 1000;

    a = (int*)malloc(n*sizeof(int));
    b = (int*)malloc(n*sizeof(int));
    c = (int*)malloc(n*sizeof(int));

    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = i*2;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels async(1)
        {
            for(int i=0; i<n; i++){
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc wait(1)

        for(int i=0; i<n; i++){
            if(c[i] != a[i] + b[i]){
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);
    free(c);

    if(err){
        printf("Test failed\n");
        return 1;
    }
    else{
        printf("Test passed\n");
        return 0;
    }
}