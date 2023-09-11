#ifndef T1
!T1:acc deviceptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(c_ptr) :: device_ptr
        
        ! Allocate a host array
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_array
        ALLOCATE(host_array(10))
        
        ! Copy the host array to the device
        CALL acc_copyin(host_array)
        
        ! Get the device pointer for the host array
        device_ptr = acc_deviceptr(host_array)
        
        ! Check that the device pointer is not null
        IF (device_ptr .eq. C_NULL_PTR) THEN
          errors = errors + 1
        END IF
        
        ! Free the host array
        DEALLOCATE(host_array)
        
        ! Check that the device pointer is still valid
        IF (acc_is_present(device_ptr) .eq. 0) THEN
          errors = errors + 1
        END IF
        
        ! Return the number of errors
        test1 = errors .eq. 0
      END
#endif