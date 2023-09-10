#ifndef T1
!T1:acc dV:2.7 t:construct-independent
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


        IF (acc_on_device(acc_get_current_device_num())) THEN
          !$acc enter data copyin(errors)
          errors = 0
          dRef = acc_deviceptr_alloc(&errors, sizeof(real *))
          IF (IS_DEVICE_PTR(dRef) .eq. false) THEN
            errors = 1
          END IF
          !$acc exit data copyout(errors)
          IF (errors .ne. 0) THEN
            test1 = .FALSE.
            EXIT FUNCTION
          END IF
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