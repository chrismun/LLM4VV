!T1:kernels construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: y
        INTEGER, DIMENSION(10):: num_gangs = (/10, 10, 10, 10, 10, 10, 10, 10, 10, 10/)
        REAL(8), DIMENSION(100, 100):: a, data

        a = 0
        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEED)
        CALL RANDOM_SEED(GET=SEED)
        data = 1

        !$acc data copy(a(1:100,1:100), data(1:100,1:100))
          !$acc kernels num_gangs(num_gangs)
            !$acc loop independent
            DO y = 1, 100
              !$acc loop independent
              DO x = 1, 100
                a(y, x) = a(y, x) + data(y, x)
              END DO
            END DO
          !$acc end kernels
        !$acc end data

        DO y = 1, 100
          DO x = 1, 100
            IF (abs(a(y, x)) .gt. 1e-10) THEN
              errors = errors + 1
              EXIT
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