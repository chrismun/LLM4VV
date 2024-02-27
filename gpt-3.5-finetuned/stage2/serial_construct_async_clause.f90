!T1:serial_construct_async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        USE OPENACC

        INTEGER :: x, errors = 0
        REAL(8),DIMENSION(LOOPCOUNT,10):: a, b, c
        REAL(8):: RAND
        INTEGER :: y

        y = x
        SEEDDIM(1) = 1
          DO y = 1, 10
            CALL RANDOM_SEED(PUT=SEED)
            CALL RANDOM_NUMBER(a(:,y))
            CALL RANDOM_NUMBER(b(:,y))
            a(:,y) = a(:,y) * 2
            b(:,y) = b(:,y) * 2
          END DO
          DO y = 1, 10
            !$acc serial loop async(y)
            DO x = 1, LOOPCOUNT
              c(x, y) = a(x, y) + b(x, y)
            END DO
          END DO
          DO y = 1, 10
            !$acc wait
            !$acc loop worker
            DO x = 1, LOOPCOUNT
              IF (abs(c(x, y) - (a(x, y) + b(x, y))) .ge. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          END DO

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