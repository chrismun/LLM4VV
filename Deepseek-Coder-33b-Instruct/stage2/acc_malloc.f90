#ifndef T1
!T1:acc malloc,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE ISO_C_BINDING
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(C_PTR) :: ptr
        INTEGER(C_SIZE_T), PARAMETER :: bytes = 1024

        ! Allocate memory on the device
        ptr = ACC_MALLOC(bytes)
        IF (.NOT. C_ASSOCIATED(ptr)) THEN
          errors = errors + 1
        END IF

        ! Deallocate memory on the device
        CALL ACC_FREE(ptr)
        IF (C_ASSOCIATED(ptr)) THEN
          errors = errors + 1
        END IF

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