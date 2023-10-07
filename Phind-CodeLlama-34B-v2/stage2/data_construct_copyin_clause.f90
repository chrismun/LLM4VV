#ifndef T1
!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b, c
        INTEGER :: i

        !$acc data copyin(a(1:10))
          !$acc parallel
            !$acc loop
            DO i = 1, 10
              a(i) = i
            END DO
          !$acc end parallel
        !$acc end data

        !$acc data copyin(b(1:10))
          !$acc kernels
            !$acc loop
            DO i = 1, 10
              b(i) = i * 2
            END DO
          !$acc end kernels
        !$acc end data

        !$acc data copyin(c(1:10))
          !$acc serial
            !$acc loop
            DO i = 1, 10
              c(i) = i * 3
            END DO
          !$acc end serial
        !$acc end data

        DO i = 1, 10
          IF (a(i) .ne. i .OR. b(i) .ne. i * 2 .OR. c(i) .ne. i * 3) THEN
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