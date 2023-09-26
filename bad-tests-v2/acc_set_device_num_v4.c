int main(){
    int failcode = 0;

    int num_devices;
    #pragma acc set device num(num_devices)

    if(num_devices <= 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}