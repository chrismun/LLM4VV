!T1:parallel construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE openacc
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x_host = 10
        INTEGER :: x_self

        ! The self clause ensures that x_self in the parallel region refers
        ! to the original host data, not a copy.
        x_self = x_host
        !$acc parallel copy(x_host) self(x_self)
            x_host = 100
            x_self = 5
        !$acc end parallel

        ! Testing if x_self remained unaffected by the parallel region as expected
        IF (x_self /= 10) THEN
          errors = errors + 1
        END IF

        ! Testing if x_host was correctly modified within the parallel region
        IF (x_host /= 100) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

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
      END PROGRAM main