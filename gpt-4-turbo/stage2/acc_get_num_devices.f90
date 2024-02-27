!T1:acc_get_num_devices,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.fh"
        
        INTEGER :: errors = 0
        INTEGER :: num_devices

        ! Testing acc_get_num_devices for CUDA-capable devices
        num_devices = acc_get_num_devices(acc_device_nvidia)
        
        ! Assuming at least 1 device is necessary for passing the test.
        ! Adjust the condition below accordingly if your environment
        ! may not have a CUDA-capable device or if you're testing for a different device type.
        IF (num_devices < 1) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.  ! No error: return .FALSE. to indicate success in Fortran logic
        ELSE
          test1 = .TRUE.   ! Error encountered: return .TRUE. to indicate a failure
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT(failcode)
      END PROGRAM