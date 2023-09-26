#include <stdio.h>
#include <openacc.h>

#pragma acc routine seq
void hello(){
    printf("Hello from GPU\n");
}

int main() {
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop gang worker vector
        for(int i = 0; i < 1; i++){
            hello();
        }
    }
    return 0;
}