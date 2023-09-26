#ifndef T1
!T1:loop construct worker clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: a, b, result
        INTEGER :: i

        !Initialize arrays
        DO i = 1, 100
          a(i) = i
          b(i) = i + 1
          result(i) = 0
        END DO

        !Stress test OpenACC worker clause
        !$ACC PARALLEL LOOP WORKER
        DO i = 1, 100
          result(i) = a(i) * b(i)
        END DO
        !$ACC END PARALLEL

        !Check if the result is correct
        DO i = 1, 100
          IF (result(i) .ne. i * (i + 1)) THEN
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
        LOGICAL, EXTERNAL :: test1
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