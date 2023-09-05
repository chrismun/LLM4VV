int main(){
    int fail = 0;
    int desired;
    int property_val;

    #pragma acc get_property(acc_device_nvidia, acc_property_max_device_id, desired)
    property_val = acc_get_property(acc_device_nvidia, acc_property_max_device_id);

    if (property_val != desired){
        fail = 1;
    }

    return fail;
}