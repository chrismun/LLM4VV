#ifndef T1
!T1:attachment counter,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, POINTER :: a, b, c
        INTEGER, TARGET :: x, y, z

        ! Allocate device memory
        ALLOCATE(a, b, c, MOLD=0)

        ! Attach pointers to target addresses
        a => x
        b => y
        c => z

        ! Check attachment counter
        IF (ACC_ATTACH(a) .NE. 1) THEN
          errors = errors + 1
        END IF
        IF (ACC_ATTACH(b) .NE. 1) THEN
          errors = errors + 1
        END IF
        IF (ACC_ATTACH(c) .NE. 1) THEN
          errors = errors + 1
        END IF

        ! Detach pointers
        CALL ACC_DETACH(a)
        CALL ACC_DETACH(b)
        CALL ACC_DETACH(c)

        ! Check attachment counter after detachment
        IF (ACC_ATTACH(a) .NE. 0) THEN
          errors = errors + 1
        END IF
        IF (ACC_ATTACH(b) .NE. 0) THEN
          errors = errors + 1
        END IF
        IF (ACC_ATTACH(c) .NE. 0) THEN
          errors = errors + 1
        END IF

        ! Deallocate device memory
        DEALLOCATE(a, b, c)

        IF (errors .eq. 0) THEN
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