#include "acc_testsuite.h"
#ifndef T1
//T1:pre,pragma,acc_getproperty,V:2.7-2.7
//T1:put_property
int test1(){
    unsigned int val;
    const char * str;

    #pragma acc parallel
    {
        val = acc_get_property(0, acc_device_nvidia, acc_property_memory);
        if (val == 0){
            return 1;
        }

        str = acc_get_property_string(0, acc_device_nvidia, acc_property_name);
        if (str == NULL){
            return 1;
        }
    }

    return 0;