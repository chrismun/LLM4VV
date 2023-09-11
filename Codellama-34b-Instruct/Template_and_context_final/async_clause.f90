#ifndef T1
!T1:async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_value
        LOGICAL :: async_flag
        
        !$acc parallel async(async_value)
        !$acc end parallel
        
        IF (async_value .eq. acc_async_sync) THEN
          async_flag = .TRUE.
        ELSE
          async_flag = .FALSE.
        END IF
        
        IF (async_flag .eqv. .FALSE.) THEN
          errors = errors + 1
        END IF
        
        !$acc parallel async(async_value)
        !$acc end parallel
        
        IF (async_value .eq. acc_async_noval) THEN
          async_flag = .TRUE.
        ELSE
          async_flag = .FALSE.
        END IF
        
        IF (async_flag .eqv. .FALSE.) THEN
          errors = errors + 1
        END IF
        
        !$acc parallel async(async_value)
        !$acc end parallel
        
        IF (async_value .eq. acc_async_sync) THEN
          async_flag = .TRUE.
        ELSE
          async_flag = .FALSE.
        END IF
        
        IF (async_flag .eqv. .FALSE.) THEN
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