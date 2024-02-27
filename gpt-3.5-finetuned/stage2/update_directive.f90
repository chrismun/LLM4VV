!T1:update directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b

        CALL RANDOM_SEED
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)

        !$acc data copy(a(1:LOOPCOUNT)) copyout(b(1:LOOPCOUNT))
          !$acc parallel loop
          DO i = 1, LOOPCOUNT
            b(i) = a(i)
          END DO
          !$acc update host(b(1:LOOPCOUNT))
        !$acc end data

        DO i = 1, LOOPCOUNT
          IF (abs(a(i) - b(i)) .gt. PRECISION) THEN
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