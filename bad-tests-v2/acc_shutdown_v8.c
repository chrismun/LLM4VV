#include "acc_testsuite.h"
#ifndef T1
//T1:shutdown,runtime,devonly,env,V:2.0-2.7
int test1(){
    #pragma acc shutdown
    return 0;