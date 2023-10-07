#include <openacc.h>

int main() {
    #pragma acc shutdown
    return 0;
}