!T1:async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async1, async2, async3
        REAL(8), DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: x

        ! Define the set of possible async values, see 216
        async1 = acc_get_default_async
        async2 = async1 + 1
        async3 = async2 + 1
        
        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT))
          !$acc parallel loop present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) async(async1)
          DO x = 1, LOOPCOUNT
            c(x) = c(x) + a(x) + b(x)
          END DO
          !$acc end parallel loop
          !$acc parallel loop present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) async(async2)
          DO x = 1, LOOPCOUNT
            c(x) = c(x) + a(x) + b(x)
          END DO
          !$acc end parallel loop
          !$acc parallel loop present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) async(async3)
          DO x = 1, LOOPCOUNT
            c(x) = c(x) + a(x) + b(x)
          END DO
          !$acc end parallel loop
          !$acc wait
        !$acc end data
        a_sum = 0
        b_sum = 0
        c_sum = 0
        DO x = 1, LOOPCOUNT
          a_sum = a_sum + a(x)
          b_sum = b_sum + b(x)
          c_sum = c_sum + c(x)
        END DO
        IF (abs(a_sum - tot) .gt. LOOPCOUNT * PRECISION) THEN
          errors = errors + 1
        END IF
        !$acc end data

        !$acc wait
        !$acc wait(async1)
        !$acc wait(async2)
        !$acc wait(async3)

        !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT))

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