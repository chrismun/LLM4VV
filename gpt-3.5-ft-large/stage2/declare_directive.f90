#ifndef T1
!T1:declare directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
	INTENT(IN) :: errors
        
        IF (acc_get_device_type() == acc_device_none) THEN
          RETURN
        END IF

        !$acc declare copyin(errors)
        !$acc parallel
          errors = 0
        !$acc end parallel
        IF (errors .ne. 0) THEN
          WRITE(*, *) 'test1:'
          WRITE(*, *) 'Failed to set errors to zero.'
          test1 = .TRUE.
          RETURN
        END IF

        test1 = .FALSE.
        RETURN
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
        CALL EXIT(failcode)
      END PROGRAM