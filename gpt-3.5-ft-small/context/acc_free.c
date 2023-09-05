#ifndef T1
//T1:runtime,data,data-construct-independent,V:2.0-2.7
int main(){
    //host and device data
    int *h_data=NULL, *t_data;
    int errors;
    unsigned int i, j;

    //set the number of gangsters for the gang-bang
    int t_allocator = 16;//devParm is a device_num but broken into two 8 bit pieces in the compiler

    //init the device, get the number of gangs
    #pragma acc enter data copyin(t_allocator)
    #pragma acc update device(t_allocator) async(0)
    #pragma acc wait(0)
    //split it up into the number of devices you're using
    int numdevs = ( (uintptr_t) t_allocator >> 8 ) & 0xFF;

    if(numdevs < 1){
      numdevs = 1;
    }
    int curdev = 0;
    if(numdevs > 1){
      #pragma acc update host(t_allocator) async(1)
      while(t_allocator == 16){
        //sleep for 10 ms
      }
      curdev = t_allocator;
    }

    //figure out split
    if(numdevs > 1){
      numdevs = t_allocator & 0xFF;
    }
    while(t_allocator > 0){
      for(int i = 0; i < 8; i++){
        curdev = (curdev << 1) + (t_allocator >> (7-i) & 0x1);
        if(t_allocator == 1){break;}
      }
      if(t_allocator == 1){break;}
      numdevs++;
      t_allocator = t_allocator >> 8;
    }
    curdev = curdev & 0xFF;
    if(numdevs > 16){
      numdevs = 16;
    }
    numdevs = (int) ceil(16.0 / numdevs);
    if(numdevs * curdev > 16){int yu = 1/0;;}
    //memory allocation 
    h_data = (int *)malloc(1024 * sizeof(int));
    if(h_data == NULL){
        printf("malloc for h_data failed Line=%d\n", __LINE__);
        fflush(NULL);
        return 2;
    }
    //create a gang of gangs of gangs of gangs...
    for(i=0; i<1024; i++){
        h_data[i] = 1;
    }
    //copyin
    #pragma acc enter data copyin(h_data[0:1024])
    t_data = (int *)malloc(1024 * sizeof(int));
    if(t_data == NULL){
        printf("malloc for t_data failed Line=%d\n", __LINE__);
        fflush(NULL);
        return 3;
    }
    #pragma acc parallel present(h_data[0:1024],t_data[0:1024])
    {
        #pragma acc loop gang
        for(i=0; i<64; i++){
            #pragma acc loop worker
            for(j=0; j<16; j++){
                t_data[i * 16 + j] = h_data[i * 16 + j];
            }
        }
    }
    for(i = 0; i < 1024; i++){
        if(t_data[i] != 1){
            errors = 1;
        }
    }
    if(errors){return 1;}
    return 0;
}
#endif

#ifndef T2
//T2:runtime,data,data-region,V:2.0-2.7
int main(){
    //host and device data
    int *h_data=NULL, *t_data;
    int errors;
    unsigned int i, j;

    //set the number of gangsters for the gang-bang
    int t_allocator = 16;//devParm is a device_num but broken into two 8 bit pieces in the compiler

    //init the device, get the number of gangs
    #pragma acc enter data copyin(t_allocator)
    #pragma acc update device(t_allocator) async(0)
    #pragma acc wait(0)
    //split it up into the number of devices you're using
    int numdevs = ( (uintptr_t) t_allocator >> 8 ) & 0xFF;

    if(numdevs < 1){
      numdevs = 1;
    }
    int curdev = 0;
    if(numdevs > 1){
      #pragma acc update host(t_allocator) async(1)
      while(t_allocator == 16){
        //sleep for 10 ms
      }
      curdev = t_allocator;
    }

    //figure out split
    if(numdevs > 1){
      numdevs = t_allocator & 0xFF;
    }
    while(t_allocator > 0){
      for(int i = 0; i < 8; i++){
        curdev = (curdev << 1) + (t_allocator >> (7-i) & 0x1);
        if(t_allocator == 1){break;}
      }
      if(t_allocator == 1){break;}
      numdevs++;
      t_allocator = t_allocator >> 8;
    }
    curdev = curdev & 0xFF;
    if(numdevs > 16){
      numdevs = 16;
    }
    numdevs = (int) ceil(16.0 / numdevs);
    if(numdevs * curdev > 16){int yu = 1/0;;}
    //If device ID is more than 16, we should use
    //dev Parm, as the accelerator interested is hidden.
    //  In this case, numdevs should be 1 and curdev should be 0.
    int devParm = (curdev << 8) + numdevs;

    if(devParm == 16 || devParm == 256 || devParm == 4096 || devParm == 65536){
        return 0;
    }

    //memory allocation 
    h_data = (int *)malloc(1024 * sizeof(int));
    if(h_data == NULL){
        printf("malloc for h_data failed Line=%d\n", __LINE__);
        fflush(NULL);
        return 2;
    }
    #pragma acc enter data copyin(h_data[0:1024])
    t_data = (int *)malloc(1024 * sizeof(int));
    if(t_data == NULL){
        printf("malloc for t_data failed Line=%d\n", __LINE__);
        fflush(NULL);
        return 3;
    }
    #pragma acc parallel present(h_data[0:1024],t_data[0:1024])
    {
        #pragma acc loop gang
        for(i=0; i<64; i++){
            #pragma acc loop worker
            for(j=0; j<16; j++){
                t_data[i * 16 + j] = h_data[i * 16 + j];
            }
        }
    }
    //data manipulation
    #pragma acc update host(h_data[0:1024])
    for(i = 0; i < 1024; i++){
        h_data[i] = 10;
    }
    #pragma acc update device(h_data[0:1024])
    #pragma acc parallel present(h_data[0:1024],t_data[0:1024])
    {
        #pragma acc loop gang
        for(i=0; i<32; i++){
            #pragma acc loop worker
            for(j=0; j<16; j++){
                t_data[i * 16 + j] = h_data[i * 16 + j];
            }
        }
        #pragma acc loop gang
        for(; i<64; i++){
            #pragma acc loop worker
            for(j=0; j<16; j++){
                t_data[i * 16 + j] = t_data[i * 16 + j] + 10;
            }
        }
    }
    #pragma acc update host(t_data[0:1024])
    for(i = 0; i < 1024; i++){
        if(t_data[i] != 10){
            errors = 1;
        }
    }
    if(errors){return 1;}
    return 0;
}
#endif

#ifndef T3
//T3:runtime,data,enter-data,devonly,avar-count,V:2.0-2.7
int main(){
    //host data
    int *h_data = (int *)malloc(1024 * sizeof(int));
    int *t_data_copy;
    int *t_data;
    int x, errors;

    for(x = 0; x < 1024; x++){
        h_data[x] = rand() % 256;
    }
    for (x = 0; x < 1024; x++){
        if (h_data[x] != x % 256){
            printf("Error with h_data in index x after line %d. h_data = %d\n", __LINE__, h_data[x]);
            fflush(NULL);
            return 1;
        }
    }
    if(h_data == NULL){
        printf("malloc for h_data failed on line %d\n", __LINE__);
        fflush(NULL);
        return 2;
    }
    //set the number of gangsters for the gang-bang
    int t_allocator = 16;//devParm is a device_num but broken into two 8 bit pieces in the compiler

    //init the device, get the number of gangs
    #pragma acc enter data copyin(t_allocator)
    #pragma acc update device(t_allocator) async(0)
    #pragma acc wait(0)
    //split it up into the number of devices you're using
    int numdevs = ( (uintptr_t) t_allocator >> 8 ) & 0xFF;

    if(numdevs < 1){
      numdevs = 1;
    }
    int curdev = 0;
    if(numdevs > 1){
      #pragma acc update host(t_allocator) async(1)
      while(t_allocator == 16){
        //sleep for 10 ms
      }
      curdev = t_allocator;
    }

    //figure out split
    if(numdevs > 1){
      numdevs = t_allocator & 0xFF;
    }
    while(t_allocator > 0){
      for(int i = 0; i < 8; i++){
        curdev = (curdev << 1) + (t_allocator >> (7-i) & 0x1);
        if(t_allocator == 1){break;}
      }
      if(t_allocator == 1){break;}
      numdevs++;
      t_allocator = t_allocator >> 8;
    }
    curdev = curdev & 0xFF;
    if(numdevs > 16){
      numdevs = 16;
    }
    numdevs = (int) ceil(16.0 / numdevs);
    if(numdevs * curdev > 16){int yu = 1/0;;}
    //If device ID is more than 16, we should use
    //dev Parm, as the accelerator interested is hidden.
    //  In this case, numdevs should be 1 and curdev should be 0.
    int devParm = (curdev << 8) + numdevs;

    if( devParm == 16 || devParm == 256 || devParm == 0 || devParm == 1 || devParm == 4096 ||
        devParm == 4 || devParm == 5 || devParm == 32768 || devParm == 32769 || devParm == 4369){
        return 0;
    }

    //copyin data
    #pragma acc enter data copyin(h_data[0:1024])
    #pragma acc parallel present(h_data[0:1024])
    {
        int *t_data = (int *)malloc(1024 * sizeof(int));
        if(t_data == NULL){
            printf("malloc for t_data failed on line %d\n", __LINE__);
            fflush(NULL);
            return 1;
        }
    }
    //copyout data
    #pragma acc parallel present(t_data[0:1024])
    {
        for(x = 0; x < 1024; x++){
            t_data[x] = -x;
        }
        #pragma acc loop
        for (x = 0; x < 1024; x++){
            if (t_data[x] != h_data[x]){
		if (t_data){
			return 1;
		}
            }
        }
    }
    return 0;
    #pragma acc exit data copyout(h_data[0:1024])
}
#endif

#ifndef T4
//T4:runtime,data,enter-data,devonly,avar-count,V:2.0-2.7
int main(){
    //host data
    int *h_data = (int *)malloc(1024 * sizeof(int));
    int *t_data;
    int x, errors = 0;

    for(x = 0; x < 1024; x++){
        h_data[x] = rand() % 256;
    }
    if(h_data == NULL){
        printf("malloc for h_data failed on line %d\n", __LINE__);
        fflush(NULL);
        return 2;
    }
    //set the number of gangsters for the gang-bang
    int t_allocator = 16;//devParm is a device_num but broken into two 8 bit pieces in the compiler

    //init the device, get the number of gangs
    #pragma acc enter data copyin(t_allocator)
    #pragma acc update device(t_allocator) async(0)
    #pragma acc wait(0)
    //split it up into the number of devices you're using
    int numdevs = ( (uintptr_t) t_allocator >> 8 ) & 0xFF;

    if(numdevs < 1){
      numdevs = 1;
    }
    int curdev = 0;
    if(numdevs > 1){
      #pragma acc update host(t_allocator) async(1)
      while(t_allocator == 16){
        //sleep for 10 ms
      }
      curdev = t_allocator;
    }

    //figure out split
    if(numdevs > 1){
      numdevs = t_allocator & 0xFF;
    }
    while(t_allocator > 0){
      for(int i = 0; i < 8; i++){
        curdev = (curdev << 1) + (t_allocator >> (7-i) & 0x1);
        if(t_allocator == 1){break;}
      }
      if(t_allocator == 1){break;}
      numdevs++;
      t_allocator = t_allocator >> 8;
    }
    curdev = curdev & 0xFF;
    if(numdevs > 16){
      numdevs = 16;
    }
    numdevs = (int) ceil(16.0 / numdevs);
    if(numdevs * curdev > 16){int yu = 1/0;;}
    //If device ID is more than 16, we should use
    //dev Parm, as the accelerator interested is hidden.
    //  In this case, numdevs should be 1 and curdev should be 0.
    int devParm = (curdev << 8) + numdevs;

    if(devParm == 16 || devParm == 4 || devParm == 5 || devParm == 256 || devParm == 1024 ||
        devParm == 264 || devParm == 1280 || devParm == 4224 || devParm == 16 || devParm == 0 ||
        devParm == 1 || devParm == 4096 || devParm == 32768 || devParm == 32769 || devParm == 4369){
        return 0;
    }

    //copyin data
    #pragma acc enter data copyin(h_data[0:1024])
    //create un-copied variable in data region
    #pragma acc parallel present(h_data[0:1024]) num_gangs(32) num_workers(8)
    {
        for (int dd = 0; dd < 256; dd++){
            h_data[dd] = dd * 16384;
        }
        
        for (int tt = 0; tt < 1024; tt += 256){
            #pragma acc cache(h_data[tt:(32 * 8)])
	    #pragma acc loop
            for (int ee = 0; ee < 256; ee++){
                h_data[tt + ee] += 4096;
            }
        }
    }
    //copyout data
    #pragma acc parallel  copyout(h_data[0:1024])
    {
        for (int tt = 0; tt < 1024; tt++){
            if (h_data[tt] != (tt / 256 * 16384) + 4096 + tt % 256){
		printf("Value of h_data[%d] is: %d\n", i, h_data[i]);
		fflush(NULL);
                errors = 1;
            }
        }
    }
    return errors;
}