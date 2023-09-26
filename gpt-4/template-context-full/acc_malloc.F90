#ifndef T1
!T1:acc malloc,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE ISO_C_BINDING, ONLY: C_PTR, C_SIZE_T, C_NULL_PTR, C_F_POINTER
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        type(C_PTR) :: devicePtr
        integer(C_PTR) :: size
        integer, dimension(:), pointer :: hostArray
        integer, dimension(:), deviceptr :: deviceArray

        size = 5 * sizeof(integer)
        devicePtr = acc_malloc(size)

        IF (C_ASSOCIATED(devicePtr, C_NULL_PTR)) THEN
          errors = errors + 1
        ELSE
          CALL C_F_POINTER(devicePtr, deviceArray, (/size/))

          ! Ensure array is accessible in device
          !$ACC ENTER DATA CREATE(deviceArray)

          IF ( .NOT. acc_is_present(deviceArray, size*sizeof(integer)) ) THEN
            errors = errors + 1
          END IF

          !$ACC EXIT DATA DELETE(deviceArray)
          CALL acc_free(devicePtr)
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
        
      END FUNCTION
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