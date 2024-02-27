!T1:serial construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, VALUE :: originalValue = 10
        INTEGER :: x = originalValue

        ! The firstprivate clause ensures x is initialized with its original value
        ! at the beginning of each serial region and changes made to x inside the serial
        ! region do not affect its value outside of the region.

        !$acc serial firstprivate(x)
          x = x + 5 
        !$acc end serial

        ! If the firstprivate clause works, x should retain its original value outside 
        ! the serial region, which is 'originalValue'. We test this logic.
        IF (x /= originalValue) THEN
          errors = errors + 1
        END IF

        ! Return FALSE (0) if no errors, TRUE (nonzero) otherwise
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