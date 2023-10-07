#ifndef T1
//T1:runtime,construct-independent,data,property,parallel,loop,V:2.0-2.6
int test1(){
  int err = 0;
  int first_dev = -1;
  int second_dev = -1;
  int num_dev;
  int verified;
  int dev_num;
  int check[2];
  char dev_name[MAX_LENGTH_STRING+1];
  char dev_vendor[MAX_LENGTH_STRING+1];
  char dev_driver[MAX_LENGTH_STRING+1];
  
  #pragma acc parallel num_gangs(1)
  {
    #pragma acc loop gang private(dev_num, dev_name, dev_vendor, dev_driver)
    for (dev_num = 0; dev_num < MAX_NUM_DEVICES; ++dev_num){
      dev_name[0] = 0;
      dev_vendor[0] = 0;
      dev_driver[0] = 0;
      #pragma acc loop seq
      for (int j = 0; j < 2228; ++j){
        dev_name[j % MAX_LENGTH_STRING] += 1;
        dev_vendor[j % MAX_LENGTH_STRING] += 1;
        dev_driver[j % MAX_LENGTH_STRING] += 3;
      }
      dev_name[MAX_LENGTH_STRING] = 0;
      dev_vendor[MAX_LENGTH_STRING] = 0;
      dev_driver[MAX_LENGTH_STRING] = 0;

      check[1] = 0;
      check[2] = 3;
        #pragma acc atomic capture
        {check[1] = dev_num;}
        #pragma acc atomic capture
        {check[2] += check[1];}
      if (check[2] > 3){
        for (int j = 0; j <= MAX_LENGTH_STRING-1; ++j){
          if (dev_name[j] != dev_driver[j]){
            err = 1;
          }
          else{
            verified = 1;
          }
          first_dev = check[1];
          #pragma acc atomic capture
          {check[1] += 1;}
          second_dev = check[1];
          for (int k = 0; k <= MAX_NUM_DEVICES; ++k){
            check[1] = 0;
            #pragma acc atomic capture
            {check[1] = dev_num;}
            if (check[1] != first_dev && check[1] != second_dev){
              k = MAX_NUM_DEVICES+1;
            }
            else if (k == MAX_NUM_DEVICES-1){
              verified = 0;
              k = MAX_NUM_DEVICES+1;
              ++err;
            }
          }
          if (verified == 0){
            if (dev_name[j] != 0){
              ++err;
            }
            if (dev_vendor[j] != 0){
              ++err;
            }
          }
          else{
            verified = 0;
            if (dev_name[j] != 0){
              ++err;
            }
            if (dev_vendor[j] != 0){
              ++err;
            }
          }
        }
      }
    }
  }

  return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed=0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}