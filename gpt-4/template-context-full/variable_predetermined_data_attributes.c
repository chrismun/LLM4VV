#include "acc_testsuite.h"
#ifndef T1
/*T1:variable predetermined data attributes,V:2.0-2.7*/

#define ARRAY_SIZE 100

int test1(){
    int errors = 0; 
    int i;
    float a[ARRAY_SIZE];
    float b[ARRAY_SIZE];
    float c[ARRAY_SIZE];

    srand(SEED);
    for (i = 0; i < ARRAY_SIZE; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    #pragma acc parallel loop private(i)
    for (i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    for (i = 0; i < ARRAY_SIZE; i++) {
        if(abs(c[i] - (a[i]+b[i])) > 0.0001){
            errors++;
        }
    }

    return errors;
}
#endif

int main(){
    int failcode = 0;
    int errors;
#ifndef T1
    errors = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i){
        errors += test1();
    }
    if (errors != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}