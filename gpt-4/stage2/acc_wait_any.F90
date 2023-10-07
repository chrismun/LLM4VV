#ifndef T1
!T1:acc wait any,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(2) :: async_ids
        INTEGER :: retval
        
        async_ids(1) = acc_async_noval
        async_ids(2) = acc_async_sync

        !$acc parallel async(async_ids(1))
        !$acc end parallel

        retval = acc_wait_any(2, async_ids)
        IF(retval == -1) THEN
            errors = errors + 1
        END IF

        async_ids(1) = acc_async_sync
        async_ids(2) = acc_async_noval

        !$acc parallel async(async_ids(2))
        !$acc end parallel

        retval = acc_wait_any(2, async_ids)
        IF(retval != -1) THEN
            errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL, EXTERNAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          IF(test1()) THEN
            failed = .TRUE.
            EXIT
          END IF
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main