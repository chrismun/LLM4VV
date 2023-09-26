#ifndef T1
!T1:data construct no_create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, POINTER :: ptr(:)
        INTEGER, TARGET :: array(10)

        !$acc data no_create(array)
        !$acc end data

        !$acc data no_create(ptr)
        !$acc end data

        !$acc parallel present(array, ptr)
        !$acc end parallel

        !$acc data no_create(array)
        !$acc end data

        !$acc data no_create(ptr)
        !$acc end data

        !$acc kernels present(array, ptr)
        !$acc end kernels

        !$acc data no_create(array)
        !$acc end data

        !$acc data no_create(ptr)
        !$acc end data

        !$acc serial present(array, ptr)
        !$acc end serial

        !$acc data no_create(array)
        !$acc end data

        !$acc data no_create(ptr)
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