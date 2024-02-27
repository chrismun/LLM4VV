!T1:acc memcpy device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b !Define the arrays a and b to test for equal data.
        REAL(8),DIMENSION(LOOPCOUNT):: c, d ! arrays c and d are used to test the presence of data on the device.
        INTEGER:: x
        
        SEEDDIM(1) = 2
        CALL RANDOM_SEED(PUT=SEEDDIM)


        CALL RANDOM_NUMBER(a) 
        b = a
        c = 0
        d = 0

        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(c(1:LOOPCOUNT), d(1:LOOPCOUNT))
        !$acc update device(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
        !$acc parallel loop
          DO x = 1, LOOPCOUNT
            c(x) = a(x)
            d(x) = b(x)
          END DO
        !$acc end parallel
        !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT), d(1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          IF (c(x) .ne. 0) THEN
            IF (c(x) .ne. d(x)) THEN
              errors = errors + 1
              PRINT*, c(x)
              PRINT*, d(x)
            END IF
          END IF
          IF (d(x) .ne. b(x)) THEN
            errors = errors + 1
            PRINT*, "Second error!"
            PRINT*, d(x)
            PRINT*, b(x)
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