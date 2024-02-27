!T1:acc wait,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: wait_arg
        INTEGER :: dev_num

        ! Initialize wait_arg and dev_num
        wait_arg = 0
        dev_num = 0

        ! Call acc_wait
        CALL acc_wait(wait_arg)

        ! Call acc_wait_device
        CALL acc_wait_device(wait_arg, dev_num)

        ! Call acc_wait_all
        CALL acc_wait_all()

        ! Call acc_wait_all_device
        CALL acc_wait_all_device(dev_num)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END