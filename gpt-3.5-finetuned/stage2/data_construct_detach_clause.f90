!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: x, deviceid, isHost
        real(8) :: runtime
        isHost = 1
        !$acc enter data copyin(isHost)
        !$acc parallel present(isHost)
          isHost = 0
        !$acc end parallel
        
        SEEDDIM(1) = 1
            SEEDDIM(1) = ENV_SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        !$acc enter data create(c(1:LOOPCOUNT))
        !$acc parallel present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
          !$acc loop
          DO x = 1, LOOPCOUNT
            c(x) = c(x) + a(x) + b(x)
          END DO
        !$acc end parallel 
        IF (isHost .eq. 0) THEN
          !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) detach(c(1:LOOPCOUNT))
        ELSE
          !$acc exit data copyout(c(1:LOOPCOUNT))
        END IF
        DO x = 1, LOOPCOUNT
          IF (abs(c(x)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO 

        ! check the correctness of the code here

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