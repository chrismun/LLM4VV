#ifndef T1
!T1:serial construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: x, y, z
        INTEGER :: i

        !$ACC SERIAL
          DO i = 1, 100
            x(i) = i
            y(i) = i
          END DO
        !$ACC END SERIAL

        !$ACC SERIAL WAIT
          DO i = 1, 100
            z(i) = x(i) + y(i)
            IF (z(i) .ne. 2 * i) THEN
              errors = errors + 1
            END IF
          END DO
        !$ACC END SERIAL

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION Test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: failcode, testrun
        LOGICAL :: failed
#ifndef T1
        LOGICAL :: test1
#endif
        failcode = 0
        failed = .FALSE.
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