#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define TEST_ASYNC 2

void generate_numbers(int *x, int n) {
    for(int i = 0; i<n; i++)
        x[i] = rand() % 100;
}

int main(){
    int *a = (int*)malloc(sizeof(int)*N);
    int *b = (int*)malloc(sizeof(int)*N);
    int *c = (int*)malloc(sizeof(int)*N);

    generate_numbers(a, N);
    generate_numbers(b, N);

    //computed with async
    #pragma acc parallel loop async(TEST_ASYNC) copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for(int i=0; i<N; i++){
        c[i] = a[i] + b[i];
    }

    //wait for async compute to finish
    acc_wait(TEST_ASYNC);

    //test if compute is done correctly
    int error = 0;
    for(int i=0; i<N; i++){
        if(c[i] != a[i] + b[i]){
            error = 1;
            printf("Error at index %d, expected %d, but got %d!\n", i, a[i]+b[i], c[i]);
            break;
        }
    }

    if(!error) printf("No errors found. Test is successful!\n");

    free(a);
    free(b);
    free(c);

    return 0;