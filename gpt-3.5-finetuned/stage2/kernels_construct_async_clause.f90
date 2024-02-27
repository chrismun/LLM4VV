!T1:kernels construct async,V:2.7-3.0
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: x, y !Iterators
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c, sum
        REAL(8),DIMENSION(LOOPCOUNT, 10):: d
        INTEGER :: errors, temp, asyncID, offset
        errors = 0
        SEEDDIM(1) = 1

        REWIND (16)
        READ (16, *) offset
        offset = 0
        REWIND (16)
        WRITE (16, *) offset

        initial_data(a, LOOPCOUNT, 2357)
        initial_data(b, LOOPCOUNT, 2357)
        initial_data(c, LOOPCOUNT, 2357)
        initial_data_10(d, LOOPCOUNT, 2367)

        sum = 0
        temp = 16777216
        !$acc data copyin(d(1:LOOPCOUNT, 1:10)) copyout(sum)
          !$acc kernels loop vector async(temp)
          DO x = 1, LOOPCOUNT
            sum(x) = 0
            DO y = 1, 10
              sum(x) = sum(x) + (a(x) + b(x) + c(x)) * d(x, y)
            END DO
          END DO
          !$acc end kernels
          !$acc update host(sum) async(temp)
         !$acc end data
        !$acc wait
        DO x = 1, LOOPCOUNT
          DO y = 1, 10
            sum = sum - (a(x) + b(x) + c(x)) * d(x, y)
          END DO
        END DO

        DO x = 1 + offset, LOOPCOUNT
          IF (abs(sum(x)) .gt. PRECISION) THEN
            errors = errors + 1
            EXIT
          END IF
        END DO

        !$acc exit data delete(d(1:LOOPCOUNT, 1:10))

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