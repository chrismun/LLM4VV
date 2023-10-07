#ifndef T1
!T1:acc detach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: host_array, device_array
        TYPE(C_PTR) :: host_ptr, device_ptr

        host_array = 1
        device_array = 2

        host_ptr = C_LOC(host_array(1))
        device_ptr = C_LOC(device_array(1))

        ! Attach device_ptr to host_ptr
        CALL acc_attach_ptr(host_ptr, device_ptr, 10*4_8)

        ! Detach device_ptr from host_ptr
        CALL acc_detach_ptr(host_ptr, device_ptr)

        ! Check if device_array is updated with host_array values
        IF (ANY(device_array .NE. host_array)) THEN
          errors = errors + 1
        END IF

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