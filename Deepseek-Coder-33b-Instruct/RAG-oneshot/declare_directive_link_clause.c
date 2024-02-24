#include <stdlib.h>
#include <stdio.h>

#pragma acc routine seq
void print_message(const char *message) {
    printf("%s\n", message);
}

int main() {
    const char *message = "Hello, World!";

    #pragma acc data copyin(message)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < 10; i++) {
                #pragma acc update device(message)
                print_message(message);
            }
        }
    }

    return 0;
}