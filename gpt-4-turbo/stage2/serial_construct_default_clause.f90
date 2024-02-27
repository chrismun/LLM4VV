!T1:serial construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: array
        
        ! Populate array with initial values
        array = (/1, 2, 3, 4, 5, 6, 7, 8, 9, 10/)
        
        ! Applying serial construct with default(shared) to verify that
        ! modifications in the serial region are reflected outside.
        !$acc serial default(shared)
        array(5) = 50
        !$acc end serial
        
        ! errors = 0 indicates success; if array(5) != 50, the default(shared) failed
        IF (array(5) /= 50) THEN
          errors = errors + 1
        END IF

        ! Check errors
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