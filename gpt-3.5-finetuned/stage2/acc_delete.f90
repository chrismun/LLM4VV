!T1:acc delete,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT) :: a, b, c
        
        CALL RANDOM_SEED
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data create(c(1:LOOPCOUNT))
        !$acc enter data create(c(1:LOOPCOUNT))

        !$acc parallel present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
          !$acc loop
          DO I = 1, LOOPCOUNT
            c(I) = a(I) + b(I) !error 'c' appears in a loop with an initialized value
          END DO
        !$acc end parallel

        CALL acc_delete(c(1:LOOPCOUNT))

        DO I = 1, LOOPCOUNT
          IF (abs(c(I) - (a(I) + b(I))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        CALL acc_delete(a(1:LOOPCOUNT))
        CALL acc_delete(b(1:LOOPCOUNT))

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