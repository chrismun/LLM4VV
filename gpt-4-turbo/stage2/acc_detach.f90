! Start of test code
!T1: acc detach,V:2.7-2.3
      LOGICAL FUNCTION test_acc_detach()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGE, DIMENSION(10) :: hostArray = 0
        INTEGER :: errors = 0
        INTEGER :: i
        INTEGER(acc_handle_kind) :: async = 0  ! Assume synchronous operation in this test
        
        ! Allocating device memory and attaching host array to device
        !$ACC ENTER DATA COPYIN(hostArray)
        CALL acc_attach(hostArray)
        
        ! Modifying the values in device memory
        !$ACC PARALLEL LOOP PRESENT(hostArray)
        DO i = 1, 10
          hostArray(i) = i * 2
        END DO
        
        ! Detaching the device pointer from hostArray
        CALL acc_detach(hostArray)
        
        ! Checking if the modification is reflected in the host memory
        DO i = 1, 10
          IF (hostArray(i) /= i * 2) THEN
            errors = errors + 1
          END IF
        END DO
        
        !$ACC EXIT DATA DELETE(hostArray)
        
        IF (errors .eq. 0) THEN
          test_acc_detach = .FALSE.
        ELSE
          test_acc_detach = .TRUE.
        END IF
      END FUNCTION test_acc_detach

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test_acc_detach
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test_acc_detach()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        WRITE(*,*) 'Exit code:', failcode
        STOP failcode
      END PROGRAM main
! End of test code