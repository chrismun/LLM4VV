! Include guard to avoid multiple definitions, assuming acc_testsuite.Fh defines it 
!T1:init directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Test 1: Initialize OpenACC to check if it works without specifying device.
        !$acc init

        ! Instead of directly checking errors (since we cannot catch them in standard Fortran),
        ! We can infer success/failure through querying supported devices.
        IF (acc_get_num_devices(acc_device_not_host) > 0) THEN
          ! Assuming a successful initialization lets us query device count greater than 0.
          errors = errors
        ELSE
          ! If we cannot find any devices, assume an error in initialization.
          errors = errors + 1
        END IF

        ! Test 2: Conditionally initialize when a device is available.
        !$acc init if(acc_get_num_devices(acc_device_nvidia) > 0) device_type(acc_device_nvidia)

        ! Repeat device check for specific device type (assuming nvidia for example)
        IF (acc_get_num_devices(acc_device_nvidia) > 0) THEN
          errors = errors
        ELSE
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL :: test1
        LOGICAL :: test1_result
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          test1_result = test1()
          failed = failed .OR. test1_result
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT (failcode)
      END PROGRAM