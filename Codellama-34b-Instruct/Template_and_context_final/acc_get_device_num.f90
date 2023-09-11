#ifndef T1
!T1:acc get device num,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_num
        
        ! Get the current device number
        device_num = acc_get_device_num(acc_device_kind)
        
        ! Check if the device number is valid
        IF (device_num .EQ. -1) THEN
          errors = errors + 1
        END IF
        
        IF (errors .EQ. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif