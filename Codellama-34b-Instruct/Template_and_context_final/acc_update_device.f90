#ifndef T1
!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_arg
        INTEGER :: bytes
        INTEGER :: data_arg
        INTEGER :: device_memory
        INTEGER :: local_memory
        
        ! Initialize the data section
        data_arg = 1
        bytes = 4
        local_memory = 1
        device_memory = 1
        
        ! Call the acc_update_device routine
        CALL acc_update_device(data_arg, bytes)
        
        ! Check if the data has been updated in device memory
        IF (device_memory .NE. local_memory) THEN
          errors = errors + 1
        END IF
        
        ! Call the acc_update_self routine
        CALL acc_update_self(data_arg, bytes)
        
        ! Check if the data has been updated in local memory
        IF (local_memory .NE. device_memory) THEN
          errors = errors + 1
        END IF
        
        ! Return the number of errors
        test1 = errors .EQ. 0
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM