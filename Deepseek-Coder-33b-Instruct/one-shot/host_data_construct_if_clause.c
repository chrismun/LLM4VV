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
        #pragma acc host_data if(1)
        {
            print_message(message);
        }
    }

    return 0;
}