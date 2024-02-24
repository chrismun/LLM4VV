#include <openacc.h>

int main(){
    int async_arg = acc_async_sync;
    acc_set_default_async(async_arg);
    return 0;
}