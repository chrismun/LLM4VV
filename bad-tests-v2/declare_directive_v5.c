pp
#include "acc_testsuite.h"

#pragma acc declare create(a)
int a = 10;

int main(){
    int fail = 0;

    if(a != 10){
        fail = 1;
    }

    return fail;
}