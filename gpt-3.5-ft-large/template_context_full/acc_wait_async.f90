#ifndef T1
!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        acc_init(acc_device_default)

        !$acc data copyout(pout[0:9]) create(pin[0:9]) async(1)
          !$acc parallel loop async(1)
          DO test = 0, 9
            pin(test) = test
          END DO
          !$acc wait
          !$acc parallel loop async(2)
          DO test = 0, 9
            pout(test) = pin(test)
          END DO
          !$acc end parallel loop async(2)
        !$acc end data
        acc_wait_async(1, 2)
        !$acc data copyout(ashared[0:9]) copyin(cshared[0:9])
          !$acc parallel loop async(3)
          DO test = 0, 9
            ashared(test) = cshared(test)
          END DO
          !$acc end parallel loop async(3)
          acc_wait_async(2, 3)
          !$acc update cshared[0:9] async(1)
          acc_wait_async(2, 1)
          !$acc update cshared[0:9] async(3)
          acc_wait_all_async(2)
          !$acc update cshared[0:9] async(2)
        !$acc end data
        acc_wait_all
        DO test = 0, 9
          IF (pout(test) .ne. test + 50) THEN
            errors = errors + 1
          END IF
        END DO
        DO test = 0, 9
          IF (ashared(test) .ne. test + 100) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif
#ifndef T2
!T2:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test2()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        acc_init(acc_device_default)

        ! missing test2 code 


        IF (errors .eq. 0) THEN
          test2 = .FALSE.
        ELSE
          test2 = .TRUE.
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
#ifndef T2
        LOGICAL :: test2
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
#ifndef T2
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test2()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 1
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM