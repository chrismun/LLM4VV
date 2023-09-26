int main(){
    int fail = 0;
    int count = 3;
    int wait_arg[3] = {acc_async_sync, acc_async_sync, acc_async_sync};
    int result;

    // Test call to acc_wait_any
    result = acc_wait_any(count, wait_arg);
    
    if(result != -1) {
        fail = 1;
    }

    // Test call to acc_wait_any_device
    int dev_num = 0;
    result = acc_wait_any_device(count, wait_arg, dev_num);

    if(result != -1) {
        fail = 1;
    }

    return fail;
}