#include "acc_testsuite.h"

int test(){

    int err = 0;
    int n = 1024;
    float *a, *b, *c;
  
    a = (float*)malloc(n*sizeof(float));
    b = (float*)malloc(n*sizeof(float));
    c = (float*)malloc(n*sizeof(float));

    srand(123);
    for(int i=0; i<n; i++){
        a[i] = (float) rand() / RAND_MAX;
        b[i] = (float) rand() / RAND_MAX;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) copyout(c[0:n])

    #pragma acc serial present(a,b,c)
    {
        for(int i=0; i<n; i++){
            c[i] = a[i] + b[i];
        }
    }

    #pragma acc exit data copyout(c[0:n])

    for(int i=0; i<n; i++){
        if(c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int number_of_errors = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        number_of_errors += test();
    }

    return number_of_errors;
}