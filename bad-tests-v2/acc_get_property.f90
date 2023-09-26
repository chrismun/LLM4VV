#ifndef T1
!T1:acc get property,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(KIND=acc_device_kind) :: device_type = acc_device_host
        INTEGER(KIND=acc_device_property_kind) :: property = acc_property_memory
        INTEGER(KIND=c_size_t) :: result
        CHARACTER(LEN=1024) :: string_result

        result = acc_get_property(0, device_type, property)
        IF (result .EQ. 0) THEN
          errors = errors + 1
        END IF

        CALL acc_get_property_string(0, device_type, property, string_result)
        IF (LEN_TRIM(string_result) .EQ. 0) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION
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