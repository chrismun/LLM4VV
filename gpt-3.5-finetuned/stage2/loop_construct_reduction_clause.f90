!T1:loop construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT, 10):: a, b, extra
        REAL(8),DIMENSION(10):: total, totals
        INTEGER :: x, y, z, current_total

        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(extra)

        total = 0
        totals = 0

        !$acc data copyin(a(1:LOOPCOUNT, 1:10), b(1:LOOPCOUNT, 1:10), extra(1:LOOPCOUNT, 1:10)) copy(total(1:10)) copyout(totals(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop reduction(+:total(1:10))
            DO x = 1, LOOPCOUNT
              DO y = 1, 10
                total(y) = total(y) + a(x, y) * b(x, y)
              END DO
            END DO
            !$acc end loop
          !$acc end parallel
        !$acc end data

        DO x = 1, LOOPCOUNT
          DO y = 1, 10
            totals(x) = totals(x) + a(x, y) * b(x, y)
          END DO
        END DO

        DO x = 1, 10
          IF (totals(x) - total(x) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc data copyin(a(1:LOOPCOUNT, 1:10), b(1:LOOPCOUNT, 1:10)) copy(total(1:10))
          !$acc parallel
            !$acc loop reduction(+:totals(1:LOOPCOUNT))
            DO x = 1, 10
              DO y = 1, LOOPCOUNT
                totals(y) = totals(y) + a(y, x) * b(y, x)
              END DO
            END DO
            !$acc end loop
          !$acc end parallel
        !$acc end data

        DO x = 1, 10
          current_total = 0
          DO y = 1, LOOPCOUNT
            current_total = current_total + a(y, x) * b(y, x)
          END DO
          IF (current_total - totals(x) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc data copyin(a(1:LOOPCOUNT, 1:10), b(1:LOOPCOUNT, 1:10), extra(1:LOOPCOUNT, 1:10)) copy(total(1:10))
          !$acc parallel
            !$acc loop reduction(*:totals(1:LOOPCOUNT))
            DO x = 1, 10
              DO y = 1, LOOPCOUNT
                totals(y) = totals(y) * (a(y, x) + b(y, x) + extra(y, x))
              END DO
            END DO
            !$acc end loop
          !$acc end parallel
        !$acc end data

        DO x = 1, 10
          current_total = 1
          DO y = 1, LOOPCOUNT
            current_total = current_total * (a(y, x) + b(y, x) + extra(y, x))
          END DO
          IF (current_total - totals(x) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc data copyin(a(1:LOOPCOUNT, 1:10), b(1:LOOPCOUNT, 1:10)) copy(total(1:10))
          !$acc parallel
            !$acc loop reduction(-:totals(1:LOOPCOUNT))
            DO x = 1, 10
              DO y = 1, LOOPCOUNT
                totals(y) = totals(y) - (a(y, x) + b(y, x))
              END DO
            END DO
            !$acc end loop
          !$acc end parallel
        !$acc end data

        DO x = 1, 10
          current_total = 0
          DO y = 1, LOOPCOUNT
            current_total = current_total - (a(y, x) + b(y, x))
          END DO
          IF (current_total - totals(x) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
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