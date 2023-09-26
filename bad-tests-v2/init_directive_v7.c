#include <stdio.h>
#include "openacc.h"

int main() {
    int failcode = 0;    

    printf("OpenACC compiler testing suite. \n");

    int var = 5;
    
    #pragma acc enter data copyin(var)
    
    int deviceVar;
    #pragma acc init
    {
        #pragma acc serial present(var)
        {
            deviceVar = var;
        }
    }
    #pragma acc exit data copyout(deviceVar)

    if (var == deviceVar) {
        printf("Passed\n");
    } else {
        printf("Failed\n");
        failcode = 1;
    }

    return failcode;
}