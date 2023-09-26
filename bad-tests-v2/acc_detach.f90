#ifndef T1
!T1:acc detach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_ptr
        INTEGER :: host_ptr
        INTEGER :: async_arg
        
        ! Create a device pointer
        device_ptr = acc_malloc(100)
        
        ! Create a host pointer
        host_ptr = acc_malloc(100)
        
        ! Attach the host pointer to the device pointer
        CALL acc_attach(host_ptr, device_ptr)
        
        ! Detach the host pointer from the device pointer
        CALL acc_detach(host_ptr, device_ptr)
        
        ! Finalize the detach
        CALL acc_detach_finalize(host_ptr, device_ptr)
        
        ! Check for errors
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM