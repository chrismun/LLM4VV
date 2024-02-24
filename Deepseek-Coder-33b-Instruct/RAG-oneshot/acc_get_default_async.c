#include <stdio.h>
#include <openacc.h>

int main() {
    int default_async = acc_get_default_async();
    printf("Default async value: %d\n", default_async);
    return 0;
}