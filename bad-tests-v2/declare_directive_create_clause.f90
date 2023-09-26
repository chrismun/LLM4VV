#ifndef T1
!T1:declare directive create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, POINTER :: ptr(:)
        INTEGER, ALLOCATABLE :: alloc_array(:)

        !$acc declare create(ptr, alloc_array)

        IF (ASSOCIATED(ptr)) THEN
          errors = errors + 1
        END IF

        ALLOCATE(alloc_array(10))

        IF (.NOT. ASSOCIATED(alloc_array)) THEN
          errors = errors + 1
        END IF

        !$acc enter data create(ptr, alloc_array)

        IF (.NOT. ASSOCIATED(ptr)) THEN
          errors = errors + 1
        END IF

        IF (.NOT. ASSOCIATED(alloc_array)) THEN
          errors = errors + 1
        END IF

        !$acc exit data delete(ptr, alloc_array)

        IF (ASSOCIATED(ptr)) THEN
          errors = errors + 1
        END IF

        IF (ASSOCIATED(alloc_array)) THEN
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