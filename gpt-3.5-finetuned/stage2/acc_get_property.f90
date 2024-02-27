!T1:acc get property,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Getting the device name and checking if it is a non-empty string
        INTEGER, PARAMETER :: ACC_DEVICE_NAME = 101  
        CHARACTER(256) :: device_name
        IF (acc_get_device_type() == acc_device_none) THEN
          CALL acc_get_property_string(0, acc_device_host, ACC_DEVICE_NAME, device_name)
          IF (LEN_TRIM(device_name) .eq. 0) THEN
            errors = errors + 1
          END IF
        ELSE
          CALL acc_get_property_string(0, acc_device_default, ACC_DEVICE_NAME, device_name)
          IF (LEN_TRIM(device_name) .eq. 0) THEN
            errors = errors + 1
          END IF
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
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
        CALL EXIT (failcode)
      END PROGRAM