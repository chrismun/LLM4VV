#ifndef T1
//T1: set,async,syntactic,V:2.0-2.7
int test1(){
    int err = 0;
    if (acc_get_device_type() == acc_device_nvidia){
        #pragma acc set device_type(nvidia) if(is_present(a)) default_async(none)
        {
          acc_async_test();
        }
    }
    if (acc_async_test()){
      err += 1;
    }

    return err;
}
#endif

int main(){
    int failed = 0;
#ifndef T1
    failed += test1();
#endif
    return failed;
}