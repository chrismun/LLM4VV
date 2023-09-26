#ifndef T1
!T1:data construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_type = 0
        INTEGER :: async = 0
        INTEGER :: wait = 0
        INTEGER :: deviceptr = 0
        INTEGER :: attach = 0
        INTEGER :: default = 0
        INTEGER :: present = 0
        INTEGER :: create = 0
        INTEGER :: no_create = 0
        INTEGER :: copy = 0
        INTEGER :: copyin = 0
        INTEGER :: copyout = 0
        INTEGER :: var_list(10)
        INTEGER :: i
        
        !$acc data device_type(device_type) async(async) wait(wait) deviceptr(deviceptr) attach(attach) default(default) present(present) create(create) no_create(no_create) copy(copy) copyin(copyin) copyout(copyout)
        DO i = 1, 10
          var_list(i) = i
        END DO
        !$acc end data
        
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