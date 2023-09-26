#ifndef T1
//T1:construct-independent,if-independent,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(5 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(5 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 5; ++y){
            b[x + y * n] = rand() / (real_t)(RAND_MAX / 10);
            c[x + y * n] = 0;
        }
    }
    #pragma acc enter data copyin(b[0:5*n])
    #pragma acc data present(b[0:5*n]) create(a[0:n]) copyout(c[0:5*n])
    {
        #pragma acc host_data use_device(b) if(0)
        {
            for (int x = 0; x < n; ++x){
                a[x] = 1;
            }
        }
        #pragma acc parallel present(a[0:n], b[0:5*n]) num_gangs(5) if(0)
        {
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 5; ++y){
                    c[x + y * n] = a[x] + b[x + y * n];
                }
            }
        }
    }
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 5; ++y){
            for (int x = 0; x < n; ++x){
                if (fabs(c[x + y * n] - (1 + b[x + y * n])) > PRECISION){
                    err += 1;
                }
            }
        }
    }
    return (err > 0);
}
#endif

#ifndef T2
//T2:construct-independent,if-independent,V:2.0-2.7
int test2(){
    int err = 0;
    size_t arrays_current_length = 1024;
    size_t two_percent = (size_t) ((float) arrays_current_length * 0.02);
    size_t key_array_length = two_percent;
    size_t data_array_length = two_percent;
    while (key_array_length < 1024 * 1024 * 16) {
        size_t * key_array = (size_t *) malloc(key_array_length * sizeof(size_t));
        size_t * data_array = (size_t *) malloc(data_array_length * sizeof(size_t));
        size_t * key_array_device;
        size_t * data_array_device;
        for (int x = 0; x < key_array_length; ++x) {
            key_array[x] = x;
        }
        for (int x = 0; x < key_array_length; ++x) {
            size_t randomIndex = (size_t) rand() % key_array_length;
            size_t temp = key_array[randomIndex];
            key_array[randomIndex] = key_array[x];
            key_array[x] = temp;
        }
        #pragma acc data copyin(key_array[0:key_array_length]) copydata(data_array[0:data_array_length])
        {
            #pragma acc serial if(0)
            for (int x = 0; x < data_array_length; ++x) {
                data_array[x] = 0;
            }
            #pragma acc parallel if(0)
            {
                #pragma acc loop seq
                for (int x = 0; x < key_array_length; ++x) {
                    {
                        size_t generatedNum = 1;
                        #pragma acc loop vector reduction(*:generatedNum)
                        for (int y = 0; y < data_array_length; ++y) {
                            generatedNum = (generatedNum * (key_array[x] % 13 + 1)) % 1000;
                        }
                        #pragma acc loop seq
                        for (int y = 0; y < data_array_length; ++y) {
                            data_array[y] += generatedNum;
                        }
                    }
                }
            }

        }
        for (int x = 0; x < data_array_length; ++x) {
            if (fabs(data_array[x] - key_array_length * ((key_array_length % 13 + 1)%1000)) > key_array_length * PRECISION) {
                err += 1;
            }
        }
        free(key_array);
        free(data_array);
        if (arrays_current_length < 1024 * 1024) {
            two_percent = two_percent * 2;
        } else {
            two_percent += 1024 * 1024;
        }
        arrays_current_length += two_percent;
        key_array_length = two_percent;
        data_array_length = two_percent;
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    #ifdef T1
        if (argc >= 2){
            failcode = failcode + test1();
        }
        else{
            failcode = failcode + test1() * 1000;
        }
    #endif
    #ifdef T2
        failcode = failcode + test2();
    #endif
    return failcode;
}