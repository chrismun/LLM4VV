! Example test code for testing acc_map_data functionality in Fortran

MODULE acc_test_utilities
  USE ISO_C_BINDING
  USE OPENACC
  IMPLICIT NONE
CONTAINS
  FUNCTION is_device_ptr_null(dev_ptr) RESULT(is_null)
    TYPE(C_PTR), VALUE :: dev_ptr
    LOGICAL :: is_null
    is_null = C_ASSOCIATED(dev_ptr, C_NULL_PTR)
  END FUNCTION is_device_ptr_null
END MODULE acc_test_utilities

!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE acc_test_utilities
        IMPLICIT NONE
        INTEGER, DIMENSION(10) :: host_data
        TYPE(C_PTR) :: device_ptr
        INTEGER :: i
        INTEGER :: errors = 0
        host_data = (/ (i, i=1,10) /)

        ! Allocate device memory manually (simulate acc_malloc) 
        device_ptr = acc_malloc(SIZEOF(host_data))
        IF (is_device_ptr_null(device_ptr)) THEN
          errors = errors + 1
          test1 = .TRUE.
          RETURN
        END IF

        ! Map the allocated device memory to the host_data
        CALL acc_map_data(host_data, device_ptr, SIZEOF(host_data))
        
        ! Perform a simple computation on the device
        !$acc parallel loop copyout(host_data)
        DO i = 1, 10
          host_data(i) = host_data(i) * 2
        END DO

        ! Verify the computation
        DO i = 1, 10
          IF (host_data(i) /= i*2) THEN
            errors = errors + 1
            EXIT
          END IF
        END DO
        
        ! Cleanup
        CALL acc_unmap_data(host_data)
        CALL acc_free(device_ptr)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
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
        PRINT *, "Test completed with failcode:", failcode
        STOP
      END PROGRAM main