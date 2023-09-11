#ifndef T1
!T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_arg
        TYPE(c_ptr) :: data_dev_src
        TYPE(c_ptr) :: data_host_dest
        INTEGER(c_size_t) :: bytes
        
        ! Initialize data_dev_src and data_host_dest
        data_dev_src = acc_malloc(100)
        data_host_dest = acc_malloc(100)
        
        ! Copy data from device to host
        bytes = 100
        CALL acc_memcpy_from_device(data_host_dest, data_dev_src, bytes)
        
        ! Check that the data was copied correctly
        IF (data_host_dest(1) .NE. data_dev_src(1)) THEN
          errors = errors + 1
        END IF
        
        ! Free memory
        CALL acc_free(data_dev_src)
        CALL acc_free(data_host_dest)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif