// C program to test openACC compiler implementation

#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// function to return a large integer
int large_integer() {
    return 1000000;
}

int main() {

    int var = 0;

    // If condition based on a true condition
    #pragma acc parallel loop if(large_integer()>10)
    for(int i=0; i<100; i++) {
        var += i;
    }

    if(var != ((99*100)/2)) {
        printf("Test failed!");
        return -1;
    }

    var = 0;

    // If clause based on a false condition
    #pragma acc parallel loop if(large_integer()<10)
    for(int i=0; i<100; i++) {
        var += i;
    }

    if(var != ((99*100)/2)) {
        printf("Test passed!");
        return 0;
    } else {
        printf("Test failed!");
        return -1;
    }

}