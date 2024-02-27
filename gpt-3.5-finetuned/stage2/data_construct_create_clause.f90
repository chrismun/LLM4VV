!T1:data construct create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        
        ! allocate and initialize to 0.0
        ALLOCATE(a(LOOPCOUNT), b(LOOPCOUNT), c(LOOPCOUNT))
        a = 0.0
        b = 0.0
        c = 0.0

        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(c(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
            DO i = 1, LOOPCOUNT
              c(i) = a(i) + b(i)
            END DO
          !$acc end parallel
        !$acc end data
        !$acc exit data copyout(c(1:LOOPCOUNT)) delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT))

        DO i = 1, LOOPCOUNT
          IF (abs(c(i) - 0.0) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, b, c)

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