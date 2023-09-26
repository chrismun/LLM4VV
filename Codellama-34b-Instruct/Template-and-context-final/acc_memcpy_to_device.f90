#ifndef T1
!T1:acc memcpy to device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(c_ptr) :: data_dev_dest, data_host_src
        INTEGER(c_size_t) :: bytes
        INTEGER(acc_handle_kind) :: async_arg
        
        data_dev_dest = acc_malloc(100)
        data_host_src = acc_malloc(100)
        bytes = 100
        async_arg = 0
        
        CALL acc_memcpy_to_device(data_dev_dest, data_host_src, bytes, async_arg)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif