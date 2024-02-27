!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT), PARAMETER :: a = (/13, 7, 200, 5, 8, 1, -29, 34, 11, 4/)
        REAL(8) :: b
        REAL(8), DEVICE :: c(LOOPCOUNT)

        b = 3

        !$acc data copyin(a(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
            DO i = 1, LOOPCOUNT
              c(i) = a(i) + b
            END DO
          !$acc end parallel
        !$acc end data

        DO i = 1, LOOPCOUNT
          IF (abs(c(i) - (a(i) + b)) .gt. PRECISION) THEN
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