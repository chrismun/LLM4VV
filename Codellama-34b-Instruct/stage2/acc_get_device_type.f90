#ifndef T1
!T1:acc get device type,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_type
        
        ! Set the device type to a known value
        device_type = acc_device_host
        
        ! Call acc_get_device_type to get the current device type
        device_type = acc_get_device_type()
        
        ! Check if the device type is the same as the known value
        IF (device_type .ne. acc_device_host) THEN
          errors = errors + 1
        END IF
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif