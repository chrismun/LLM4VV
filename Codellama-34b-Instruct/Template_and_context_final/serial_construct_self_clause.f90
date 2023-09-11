fortran
#ifndef T1
!T1:serial construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_type
        LOGICAL :: self_clause_present
        
        ! Check if the self clause is present
        self_clause_present = .FALSE.
        IF (PRESENT(self_clause)) THEN
          self_clause_present = .TRUE.
        END IF
        
        ! Check if the device type is the same as the current device
        device_type = acc_get_device_type()
        IF (device_type .EQ. acc_device_host) THEN
          IF (self_clause_present) THEN
            errors = errors + 1
          END IF
        ELSE IF (device_type .EQ. acc_device_not_host) THEN
          IF (.NOT. self_clause_present) THEN
            errors = errors + 1
          END IF
        END IF
        
        IF (errors .EQ. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM