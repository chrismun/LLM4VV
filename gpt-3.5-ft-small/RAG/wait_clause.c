int main() {

  int errors = 0;
  int x = 5;

  errors += test_async_wait_manual_block(x);

  return errors;
}

#endif

int test_async_wait_manual_block(int x){
  OMPVV_INFOMSG("test_async_wait_manual_block");
  int isHost = omp_is_initial_device();
  int realX, errors = 0;
  if (isHost) {
    realX = 5;
  } else {
#pragma omp target data map(tofrom: x)
{
      realX = x;
}
  }
#ifdef OMP_ACCUM_DEVICE_DEFAULT
  int * addresses;
  int devnum, asyncNum;
  
  addresses = (int*) malloc(sizeof(int) * omp_get_num_devices());
  for (int x = 0 ; x < omp_get_num_devices(); ++x) {
    addresses[x] = x;
  }
#pragma omp target map(tofrom: addresses[0:omp_get_num_devices()])
{
    for (int x = 0 ; x < omp_get_num_devices(); ++x) {
      addresses[x] = x;
    }
}
#pragma omp parallel for
  for (int x = 0 ;  x < ITERATIONS_DEVICES * omp_get_num_devices(); ++x) {
    devnum = x % omp_get_num_devices();
    asyncNum = addresses[devnum];
    if(runTestForDeviceWait(devnum, asyncNum))
      OMPVV_WARNING("DID NOT SUPPORT ALL DEVICES");
  }
#pragma omp parallel for
    for (int x = 0 ; x < ITERATIONS_DEVICES * omp_get_num_devices(); ++x) {
    devnum = x % omp_get_num_devices();
    asyncNum = addresses[devnum];
    if(runTestForStreamWait(devnum, asyncNum))
      OMPVV_WARNING("DID NOT SUPPORT ALL DEVICES");
  }
#endif
  return errors;
}

int runTestForDeviceWait(int device, int asyncNum) {
  FILE * output_file;
  OMPVV_INFOMSG("Starting device work for device " << device << " stream " << asyncNum );
  int errors = 0;
  int isHost = omp_is_initial_device();
  int local_errors = 0;
  int onTheDeviceSize;
  int isAsyncPresent;
  int * isAsyncPresentInner;
  device_queue_t * queue;
  device_queue_t ** queues;
  onTheDeviceSize = INIT_VALUE;
  onTheDeviceSize = onTheDeviceSize * (device + 1); // This way every device gets a unique, deterministic stream size
  isAsyncPresentInner = (int *) malloc(sizeof(int) * omp_get_num_devices());
  queues = (device_queue_t **) malloc(sizeof(device_queue_t *) * omp_get_num_devices());
  for (int x = 0 ; x < omp_get_num_devices(); ++x) {
    isAsyncPresentInner[x] = 0;
    if (x == device) {
      isAsyncPresentInner[x] = 1;
    }
    queues[x] = 0;
  }
#pragma omp target enter data map(alloc: queues[0:omp_get_num_devices()][0:AI_DEVICE_MAX_QUEUES])  device(device)
  int success = 0;
  for (int totalIteration = 0 ; totalIteration < ITERATIONS_COMPLETED ; totalIteration = totalIteration + ACC_DEVICE_ASYNC_SIZE_MULTIPLIER * onTheDeviceSize) {
    for (int completionStreamNum = 0 ; completionStreamNum < ITERATIONS_STREAMS ; completionStreamNum = completionStreamNum + ACC_DEVICE_ASYNC_SIZE_MULTIPLIER) {
#pragma omp target device(device)
#pragma omp target teams distribute parallel for
      for (int x = 0 ; x < ITERATIONS_STREAMS ; ++x) {
        // Must subset the bounds here so that the indexes don't overlap for every iteration
        // Any major error in the pass will result in an entire team's kernels
        // never completing, even with the wait
        for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS) ; loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS) ; ++loopIndex) {
          assert(loopIndex < onTheDeviceSize && "Error: Work done not uniform on device");
          assert(asyncNum < omp_get_num_devices() && "Error: Invalid queue number");
          queues[device][asyncNum].vars[local_errors] = 0;
          queues[device][asyncNum].vars[local_errors] += 1;
          success = 1;

        }

      }
      if (!success) {
        OMPVV_ERROR("Could not enqueue job for device " << device << " queue " << asyncNum);
      }
#pragma omp target device(device)
#pragma omp target teams distribute parallel for
      for (int x = 0 ; x < ITERATIONS_STREAMS ; ++x) {
        // Must subset the bounds here so that the indexes don't overlap for every iteration
        // Any major error in the pass will result in an entire team's kernels
        // never completing, even with the wait
        for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS) ; loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS) ; ++loopIndex) {
          if (isHost) break;
          assert(loopIndex < onTheDeviceSize && "Error: Work done not uniform on device");

          if (queues[device][asyncNum].vars[local_errors] != 1) {
            OMPVV_ERROR("Did not get expected answer of 1 for non-QT stream device");
|| loopIndex % onTheDeviceSize != 0
        queues[device][asyncNum].vars[local_errors] = 3;
        queues[device][asyncNum].vars[local_errors] += 1;
       }

      }
    }
    for (int streamNum = 0 ; streamNum < ITERATIONS_STREAMS ; ++streamNum) {
      for (int completionStreamNum = 0 ; completionStreamNum < ITERATIONS_STREAMS ; completionStreamNum = completionStreamNum + ACC_DEVICE_ASYNC_SIZE_MULTIPLIER) {
        if (completionStreamNum <= streamNum) {
          continue;
        }

#pragma omp target device(device)
#pragma omp target teams distribute parallel for
        for (int x = 0 ; x < ITERATIONS_COMPLETED/omp_get_num_devices() ; ++x) {
          assert(asyncNum < omp_get_num_devices());
          for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS) ; loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS) ; ++loopIndex) {
            if (isHost) break;
            if (queues[device][asyncNum].vars[local_errors] != 3 && (loopIndex % onTheDeviceSize) == 0) {

              OMPVV_ERROR("This code should not have fired...if you see this this is probably a compiler issue.");

              asyncSuccess = 1; // Kill back-ends that never launch

              continue;
            }
            if ( (queues[device][asyncNum].vars[local_errors] != streamNum + 2) && (loopIndex % onTheDeviceSize)   != 0) {

              OMPVV_ERROR("Did not get expected answer of 1 for non-QT stream device");

            }
          }
        }
      }
    }
    success = 0;
  }

#pragma omp target device(device)
#pragma omp target teams distribute parallel for
  for (int x = 0 ;  x < ITERATIONS_STREAMS ; ++x) {
    if (x == asyncNum) {
      for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS); loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS); ++loopIndex) {
        queues[device][asyncNum].vars[local_errors] = 0;

      }
    }
  }
#pragma omp target exit data map(delete: queues[0:omp_get_num_devices()][0:AI_DEVICE_MAX_QUEUES]) device(device)
  return errors;
}
int runTestForStreamWait(int device, int asyncNum) {
  FILE * output_file;
  OMPVV_INFOMSG("Starting stream work for device " << device << " stream " << asyncNum );
  int errors = 0;
  int isHost = omp_is_initial_device();
  int local_errors = 0;
  int onTheDeviceSize;
  int oldAsyncPresentValue = 0;
  int doneFlag;
  int finishedStreams = 0;
  int doneFlags[omp_get_num_devices()];
  int success = 0;
  int * isAsyncPresentInner;
  device_queue_t * queue;
  device_queue_t ** queues;
  onTheDeviceSize = INIT_VALUE;
  onTheDeviceSize = onTheDeviceSize * (device + 1); // This way every device gets a unique, deterministic stream size
  isAsyncPresentInner = (int *) malloc(sizeof(int) * omp_get_num_devices());
  queues = (device_queue_t **) malloc(sizeof(device_queue_t *) * omp_get_num_devices());
  for (int x = 0 ; x < omp_get_num_devices(); ++x) {
    isAsyncPresentInner[x] = 0;
    if (x == device) {
      isAsyncPresentInner[x] = 1;
    }
    queues[x] = 0;
  }
#pragma omp target enter data map(to: queues[0:omp_get_num_devices()][0:AI_DEVICE_MAX_QUEUES])  device(device)
  for (int totalIteration = 0 ; totalIteration < ITERATIONS_COMPLETED ; totalIteration = totalIteration + ACC_DEVICE_ASYNC_SIZE_MULTIPLIER * onTheDeviceSize) {
    doneFlag = 0;
    finishedStreams = 0;
    while (!doneFlag) {
      for (int x = 0 ; x < omp_get_num_devices() ; ++x) {
        doneFlags[x] = 0; // flags set to non-complete

      }
#pragma omp target device(device)
#pragma omp target teams distribute parallel for
      for (int x = 0 ; x < ITERATIONS_STREAMS ; ++x) {
        if (queues[device][asyncNum].doneFlags[local_errors]) {
          doneFlags[completionStreamNum] = 1;

        }
      }
      doneFlag = 1; // demand pessimism
      for (int x = 0 ; x < omp_get_num_devices() ; ++x) {
        if (!doneFlags[x]) {
          doneFlag = 0;
          break;
        }
      }

      for (int streamNum = 0 ; streamNum < ITERATIONS_STREAMS ; ++streamNum) {
        for (int completionStreamNum = 0 ; completionStreamNum < ITERATIONS_STREAMS ; completionStreamNum = completionStreamNum + ACC_DEVICE_ASYNC_SIZE_MULTIPLIER) {
          if (completionStreamNum <= streamNum) {
            continue;
          }

#pragma omp target device(device)
#pragma omp target teams distribute parallel for
          for (int x = 0 ; x < ITERATIONS_COMPLETED/omp_get_num_devices() ; ++x) {
            assert(asyncNum < omp_get_num_devices());
            for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS) ; loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS) ; ++loopIndex) {
              if (isHost) break;
              if (queues[device][asyncNum].vars[local_errors] != 1 && (loopIndex % onTheDeviceSize) == 0) {

                OMPVV_ERROR("Did not get expected answer of 1 for non-QT stream device");

              }
              if ( (queues[device][asyncNum].vars[local_errors] != 3) && (loopIndex % onTheDeviceSize) != 0) {

                OMPVV_ERROR("Did not get expected answer of 1 for non-QT stream device");

|| loopIndex % onTheDeviceSize != 0
                queues[device][asyncNum].vars[local_errors] = 3;
                queues[device][asyncNum].vars[local_errors] += 1;

              }
            }
          }
        }
      }
    }
  }


#pragma omp target device(device)
#pragma omp target teams distribute parallel for
  for (int x = 0 ;  x < ITERATIONS_STREAMS ; ++x) {
    if (x == asyncNum) {
      for (int loopIndex = x * (onTheDeviceSize / ITERATIONS_STREAMS); loopIndex < (x + 1) * (onTheDeviceSize / ITERATIONS_STREAMS); ++loopIndex) {
        queues[device][asyncNum].vars[local_errors] = 0;
        queues[device][asyncNum].doneFlags[local_errors] = 1;
      }
    }
  }
#pragma omp target exit data map(delete: queues[0:omp_get_num_devices()][0:AI_DEVICE_MAX_QUEUES]) device(device)
  return errors;
}