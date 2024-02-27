!T1:loop construct gang clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8) :: a(2000), b(2000), c(2000)        
        INTEGER :: i

        SEEDDIM(1) = 1
        SEEDDIM(2) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
          
        !$acc data copyin(a(1:2000), b(1:2000)) copy(c(1:2000))
          !$acc parallel
            !$acc loop gang
            DO i = 1, 100
              c(i) = a(i) + b(i)
            END DO
          !$acc end parallel
        !$acc end data

        DO i = 1, 100
          IF (abs(c(i) - (a(i) + b(i))) .gt. 1e-15) THEN
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