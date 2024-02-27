!T1:loop construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT, 10):: a, b, c
        REAL(8),DIMENSION(10):: tot
        INTEGER :: x, y, tmp

        SEEDDIM(1) = 1
        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        tot = 0

        !$acc data copyin(a(1:LOOPCOUNT,1:10), b(1:LOOPCOUNT,1:10), c(1:LOOPCOUNT,1:10)) copyout(a(1:LOOPCOUNT,1:10))
          !$acc parallel
            !$acc loop gang private(tmp)
            DO x = 1, LOOPCOUNT
              tmp = 0
              !$acc loop worker private(tmp)
              DO y = 1, 10
                tmp = tmp + b(x,y) + c(x,y)
                !$acc loop vector
                DO y = 1, 10
                  a(x,y) = a(x,y) + tmp / DIVISOR
                END DO
              END DO
            END DO
          !$acc end parallel
        !$acc end data

        DO x = 1, LOOPCOUNT
          DO y = 1, 10
            tot(y) = tot(y) + (b(x, y) + c(x, y)) / DIVISOR
          END DO
        END DO

        DO y = 1, 10
          DO x = 1, LOOPCOUNT
            IF (abs(tot(y) - a(x, y)) .gt. 3) THEN
              errors = 1
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