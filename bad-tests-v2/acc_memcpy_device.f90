#ifndef T1
!T1:acc memcpy device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: data_dev_dest, data_dev_src
        INTEGER :: bytes
        INTEGER :: async_arg
        
        ! Initialize data_dev_dest and data_dev_src
        data_dev_dest = 0
        data_dev_src = 0
        bytes = 0
        async_arg = 0
        
        ! Call acc_memcpy_device
        CALL acc_memcpy_device(data_dev_dest, data_dev_src, bytes)
        
        ! Check for errors
        IF (bytes .EQ. 0) THEN
          errors = errors + 1
        END IF
        IF (data_dev_dest .EQ. data_dev_src) THEN
          errors = errors + 1
        END IF
        IF (data_dev_src .EQ. 0) THEN
          errors = errors + 1
        END IF
        IF (data_dev_dest .EQ. 0) THEN
          errors = errors + 1
        END IF
        
        ! Return the number of errors
        test1 = errors .EQ. 0
      END
#endif