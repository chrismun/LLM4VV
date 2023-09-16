struct float4{
    float x;
    float y;
    float z;
    float w;
};

#pragma acc declare link(device_float4)

int test1(){
    int err = 0;
    srand(SEED);

    struct float4 host_float4;
    struct float4 *device_float4;

    host_float4.x = (float)rand()/(float)(RAND_MAX);
    host_float4.y = (float)rand()/(float)(RAND_MAX);
    host_float4.z = (float)rand()/(float)(RAND_MAX);
    host_float4.w = (float)rand()/(float)(RAND_MAX);   

    #pragma acc enter data create(host_float4)

    #pragma acc parallel copyin(host_float4) present(device_float4)
    {
        device_float4->x = host_float4.x;
        device_float4->y = host_float4.y;
        device_float4->z = host_float4.z;
        device_float4->w = host_float4.w;
    }
    #pragma acc exit data copyout(host_float4, device_float4[0:1])

    if (device_float4->x != host_float4.x || device_float4->y != host_float4.y ||
        device_float4->z != host_float4.z || device_float4->w != host_float4.w){
        err = 1;
    }

    return err;
}