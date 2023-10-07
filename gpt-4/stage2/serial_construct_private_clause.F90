#ifndef T1
!T1:serial construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: arr
        INTEGER, DIMENSION(10) :: result
        INTEGER :: i

        DO i = 1, 10
          arr(i) = i
        END DO

        !$ACC SERIAL PRIVATE(arr) 
          DO i = 1, 10
            result(i) = arr(i) * 2
          END DO
        !$ACC END SERIAL

        DO i = 1, 10
          IF (result(i) /= arr(i) * 2) THEN
            errors = errors + 1
          END IF
        END DO

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