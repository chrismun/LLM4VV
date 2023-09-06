#ifndef T1
//T1: acc_get_property
int test1(){
    int err = 0;
    int device_num = 0;

    if (acc_get_device_type() == acc_device_none){
        device_num = 0;
    }
    else{
        device_num = acc_get_device_num(acc_get_device_type());
    }

    if (acc_get_property(device_num, acc_get_device_type(), acc_property_memory) == 0){
        err += 1;
    }

    return err;
}
#endif

#ifndef T2
//T2: acc_get_property_string
int test2(){
    int err = 0;
    int device_num = 0;

    if (acc_get_device_type() == acc_device_none){
        device_num = 0;
    }
    else{
        device_num = acc_get_device_num(acc_get_device_type());
    }

    if (acc_get_property_string(device_num, acc_get_device_type(), acc_property_vendor) == NULL){
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}