!T1:kernels construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT):: temperature
        REAL(8):: avg = 0
        INTEGER:: x
        INTEGER :: lcv = 0
        REAL(8),DIMENSION(10, LOOPCOUNT):: data
        


        SEEDDIM(1) = 1
          SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(data)
        temperature(1:LOOPCOUNT) = 0
        DO lcv = 1, 10
          DO x = 1, LOOPCOUNT
            temperature(x) = temperature(x) + data(lcv, x)
          END DO
        END DO
        !$acc data
          !$acc kernels loop if(LOOPCOUNT .gt. 1024)
          DO lcv = 1, 10
            DO x = 1, LOOPCOUNT
              temperature(x) = temperature(x) / 10
            END DO
          END DO
        !$acc end data

          DO x = 1, LOOPCOUNT
            avg = avg + temperature(x)
          END DO
          avg = avg / LOOPCOUNT


        DO x = 1, LOOPCOUNT
          errors = errors + (temperature(x) - avg) .lt. PRECISION
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