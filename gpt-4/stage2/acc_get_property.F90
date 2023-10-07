#ifndef T1
!T1:acc get property,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER(C_SIZE_T) :: memory
        INTEGER :: dev_num, dev_type, property, errors = 0
        CHARACTER(LEN=32) :: device_name
        dev_type = ACC_DEVICE_CURRENT
        dev_num = acc_get_num(dev_type)
        IF (dev_num <= 0) THEN
          errors = errors + 1
        ELSE 
          property = acc_property_memory
          memory = acc_get_property(dev_num, dev_type, property)
          IF (memory == 0) THEN
            errors = errors + 1
          END IF
          property = acc_property_name
          CALL acc_get_property_string(dev_num, dev_type, property, device_name)
          IF (device_name .EQ. ' ') THEN
            errors = errors + 1
          END IF
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
      END PROGRAM main