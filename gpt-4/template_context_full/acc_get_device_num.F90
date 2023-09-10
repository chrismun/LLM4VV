#ifndef T1
!T1:acc get device num,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER(acc_device_kind) :: dev_type
        INTEGER :: device_num, errors = 0

        ! Initialize device
        dev_type = acc_device_nvidia
        CALL acc_set_device_type(dev_type)
        
        ! Get device number
        device_num = acc_get_device_num(dev_type)
        
        ! Check if device number is as expected
        IF (device_num == -1) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif