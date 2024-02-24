#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_nvidia);
    printf("OpenACC is supported\n");
    acc_shutdown(acc_device_nvidia);
    return 0;
}