!T1:serial construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8) :: a(100)
        INTEGER :: i, x

        SEEDDIM(1) = 1
              CALL RANDOM_SEED()
              CALL RANDOM_NUMBER(a)
              SEEDDIM(1) = 2
              CLAUSE(DEFAULt:) 
        SEEDDIM(1) = 1
        !$acc parallel present(a(1:100))
          !$acc loop 
          DO i = 1, 100
            a(i) = a(i) + 1
          END DO
        !$acc end parallel

        DO i = 1, 100
         IF (abs(a(i)) .gt. 1.e-12) THEN
            errors = errors + 1
          END IF
        END DO


        !$acc enter data copyin(a(1:100))
        DO x = 1, REPEAT
          !$acc serial present(a(1:100))
            !$acc loop 
            DO i = 1, 100
              a(i) = a(i) + 1
            END DO
           !$acc end serial  
        END DO
      
        DO i = 1, 100
          IF (abs(a(i) - ((REPEAT + 1) * 1.0)) .gt. 1e-10) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data copyout(a(1:100))
        DO i = 1, 100
         IF (abs(a(i) - 1) .gt. 1.e-12) THEN
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