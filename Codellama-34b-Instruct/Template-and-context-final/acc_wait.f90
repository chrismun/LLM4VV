#ifndef T1
!T1:acc wait,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_queue
        INTEGER :: async_handle
        INTEGER :: dev_num
        
        ! Create an asynchronous queue
        async_queue = acc_async_queue()
        
        ! Create an asynchronous handle
        async_handle = acc_async_handle()
        
        ! Set the device number
        dev_num = acc_get_device_num()
        
        ! Wait for the asynchronous operation to complete
        CALL acc_wait(async_handle, dev_num)
        
        ! Check for errors
        IF (acc_get_async_error(async_handle, dev_num) .NE. 0) THEN
          errors = errors + 1
        END IF
        
        ! Clean up
        CALL acc_async_queue_destroy(async_queue)
        CALL acc_async_handle_destroy(async_handle)
        
        IF (errors .EQ. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif