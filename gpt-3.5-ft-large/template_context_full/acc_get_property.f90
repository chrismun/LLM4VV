#ifndef T1
!T1:acc get property,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
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

      FUNCTION test1() RESULT(test_passed)
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: device_num, device_type, device_property, device_memory
        CHARACTER(LEN=128) :: device_property_string, device_name
        LOGICAL :: test_passed
        INTEGER :: errors, acc_get_property
        errors = 0

        device_num = acc_get_device_num(acc_get_device_type)
        device_type = acc_get_device_type

        device_property = acc_property_memory
        device_memory = acc_get_property(device_num, device_type, device_property)

        device_property_string = acc_get_property_string(device_num, device_type, device_property)

        device_property = acc_property_name
        device_name = acc_get_property_string(device_num, device_type, device_property)

        IF (acc_get_property(device_num, device_type, device_property) .eq. 0) THEN
          errors = errors + 1
        ELSE IF (device_memory .lt. 0) THEN
          errors = errors + 1
        END IF

        IF (LEN_TRIM(device_property_string) .eq. 0) THEN
          errors = errors + 1
        END IF

        IF (LEN_TRIM(device_name) .eq. 0) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test_passed = .FALSE.
        ELSE
          test_passed = .TRUE.
        END IF
      END FUNCTION