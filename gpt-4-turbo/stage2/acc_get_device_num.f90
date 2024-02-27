! Assuming 'acc_testsuite.Fh' file exists with common definitions if required.
! This code focuses on illustrating the testing of 'acc_get_device_num' functionality.

!T1:acc_get_device_num,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: deviceNum
        INTEGER :: errors = 0
        
        ! Testing OpenACC acc_get_device_num feature
        deviceNum = acc_get_device_num(acc_device_nvidia)

        ! If there are no NVIDIA devices or if NVIDIA devices are not supported, it returns -1.
        ! As a simple test, we verify that the function does not return -1,
        ! assuming at least one NVIDIA GPU is expected to be present.
        ! Otherwise, adapt this check to the expected device type and setup.
        IF (deviceNum == -1) THEN
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
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT(failcode)
      END PROGRAM main