#ifndef T1
!T1:declare directive link clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! global link has to be declared in the host
        !$acc declare link(C)
        REAL(8), DIMENSION(10) :: C


        !$acc data copyout(C(1:10))
          !$acc parallel
            !$acc loop
            DO I = 0, 9
              C(I + 1) = C(I + 1) + 1.0
            END DO
          !$acc end parallel
        !$acc end data


        !$acc data copyin(C(1:10))
          !$acc parallel
            !$acc loop
            DO I = 1, 10
              IF (C(I) - 1.0 .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          !$acc end parallel
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