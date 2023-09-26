#ifndef T1
!T1:acc set default async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_arg
        INTEGER :: async_default
        
        ! Set the default asynchronous activity queue to a non-default value
        async_default = acc_async_default
        async_arg = acc_async_noval
        CALL acc_set_default_async(async_arg)
        
        ! Check that the default asynchronous activity queue has been set correctly
        IF (acc_default_async_var .NE. async_arg) THEN
          errors = errors + 1
        END IF
        
        ! Reset the default asynchronous activity queue to its initial value
        CALL acc_set_default_async(async_default)
        
        ! Check that the default asynchronous activity queue has been reset correctly
        IF (acc_default_async_var .NE. async_default) THEN
          errors = errors + 1
        END IF
        
        IF (errors .EQ. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif