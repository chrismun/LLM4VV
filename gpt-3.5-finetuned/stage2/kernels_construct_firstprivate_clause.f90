!T1:kernels construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER:: errors = 0

        REAL(8) :: x1 = 3.14
        INTEGER:: x2 = 1
        REAL(8):: multipler = 1.5

        !$acc data copyin(multipler) copy(x1, x2)
          !$acc kernels firstprivate(x2)
            !$acc loop
            DO x2 = 0, 10
              x1 = x1 * multipler
            END DO
          !$acc end kernels
        !$acc end data
        DO x2 = 0, 10
          x1 = x1 * multipler
        END DO

        IF (abs(x1 - 3.14 * multipler ** 11) .gt. PRECISION) THEN
          errors = errors + 1
        END IF

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