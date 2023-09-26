#ifndef T1
!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(c_ptr) :: host_ptr
        TYPE(c_ptr) :: device_ptr
        
        ! Allocate memory on the device
        device_ptr = acc_malloc(100)
        
        ! Copy data to the device
        CALL acc_copyin(device_ptr, 100)
        
        ! Get the host pointer associated with the device pointer
        host_ptr = acc_hostptr(device_ptr)
        
        ! Check that the host pointer is not null
        IF (host_ptr .eq. C_NULL_PTR) THEN
          errors = errors + 1
        END IF
        
        ! Free the device memory
        CALL acc_free(device_ptr)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif