!T1:kernels construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: SIZE = 10
        REAL(8),DIMENSION(SIZE, SIZE):: a, b, c
        REAL(8):: RAND_SOL
        INTEGER:: test_val = 1
        INTEGER:: errors = 0

        SEEDDIM(1) = 1
        

        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc data copyin(a,b) copyout(c)
          !$acc kernels wait(test_val)
            !$acc loop
            DO i = 1, SIZE
              !$acc loop
              DO j = 1, SIZE
                c(i, j) = c(i, j) + (a(i, j) * b(i, j))
              END DO
            END DO
        !$acc end data

        DO i = 1, SIZE
          DO j = 1, SIZE
            IF (abs(c(i,j) - (a(i,j)*b(i,j))) .gt. EXP10(-6)) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        

        !$acc wait(test_val)
      

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