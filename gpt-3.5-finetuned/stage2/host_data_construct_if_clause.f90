!T1:host_data construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8) :: mult
        INTEGER :: x
        mult = 3

        SEEDDIM(1) = 1
        {
          {
            DO x = 1, LOOPCOUNT
              CALL RANDOM_SEED(PUT=SEEDDIM(x:1))
              CALL RANDOM_NUMBER(a(x))
              CALL RANDOM_NUMBER(b(x))
              a(x) = mult * a(x)
              c(x) = 0
            END DO
            {
              for x = 1, LOOPCOUNT
                a(x) = a(x) / 3
            }
            for x = 1, LOOPCOUNT
              c(x) = a(x) + b(x)
          }
        }
        DO x = 1, LOOPCOUNT
          IF (abs(a(x) - c(x)) .gt. PRECISION(a(x))) THEN
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