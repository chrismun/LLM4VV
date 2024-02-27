!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: x

        ! Creating random values
        CALL RANDOM_SEED
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data create(c(1:LOOPCOUNT))

        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
          DO x = 1, 10
            !$acc wait_async(x - 1)
            !$acc parallel loop async(x - 1)
            DO WHILE(LOOPCOUNT .gt. 1000)

            END DO
            !$acc loop async(x - 1)
            DO i = 1, LOOPCOUNT
              c(i) = a(i) + b(i)
            END DO
          END DO
        !$acc end data

        DO x = 0, 9
          CALL acc_wait_async(x)
        END DO

        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
        CALL acc_exit_data(c)
        
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