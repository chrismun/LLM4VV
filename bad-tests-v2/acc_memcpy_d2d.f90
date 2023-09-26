#ifndef T1
!T1:acc memcpy d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: dev_num_dest, dev_num_src
        INTEGER :: async_arg_src
        TYPE(acc_device_t) :: device_dest, device_src
        TYPE(acc_async_t) :: async_arg_src
        TYPE(acc_memcpy_d2d_t) :: memcpy_d2d
        
        ! Initialize the devices and async arguments
        CALL acc_init(device_dest)
        CALL acc_init(device_src)
        CALL acc_async_init(async_arg_src, device_src)
        
        ! Set the device numbers and async argument
        dev_num_dest = device_dest%device_num
        dev_num_src = device_src%device_num
        async_arg_src = async_arg_src%async_arg
        
        ! Create the memcpy_d2d object
        CALL acc_memcpy_d2d_init(memcpy_d2d, dev_num_dest, dev_num_src, async_arg_src)
        
        ! Perform the memcpy_d2d operation
        CALL acc_memcpy_d2d(memcpy_d2d, data_arg_dest, data_arg_src, bytes)
        
        ! Check for errors
        IF (acc_get_error_code() .ne. acc_error_none) THEN
          errors = errors + 1
        END IF
        
        ! Clean up
        CALL acc_memcpy_d2d_destroy(memcpy_d2d)
        CALL acc_async_destroy(async_arg_src)
        CALL acc_destroy(device_src)
        CALL acc_destroy(device_dest)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif