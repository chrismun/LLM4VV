fortran
#ifndef T1
!T1:host_data construct use_device clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_address
        INTEGER :: host_address
        INTEGER :: var
        INTEGER :: i
        
        !$acc host_data use_device(var)
        !$acc parallel loop
        DO i = 1, 10
          var = i
        END DO
        !$acc end parallel loop
        !$acc end host_data
        
        device_address = acc_get_device_address(var)
        host_address = acc_get_host_address(var)
        
        IF (device_address .ne. host_address) THEN
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