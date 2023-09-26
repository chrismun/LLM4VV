#ifndef T1
!T1:kernels construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: mult = 17
        REAL(8), ALLOCATABLE :: a(:,:)
        REAL(8), ALLOCATABLE :: a_copy(:,:)
        INTEGER :: x, y

        SEEDDIM(1) = 1
        #ifdef SEED
        SEEDDIM(1) = SEED
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        ALLOCATE(a(n, n))
        ALLOCATE(a_copy(n, n))

        CALL RANDOM_NUMBER(a)
        a_copy = a

        !$acc data copy(a(1:n, 1:n))
          !$acc kernels
            !$acc loop independent
            DO y = 1, n
              !$acc loop independent
              DO x = 1, n
                a(y, x) = a(y, x) * mult
              END DO
            END DO
          !$acc end kernels
        !$acc end data

        DO y = 1, n
          DO x = 1, n
            IF (abs(a_copy(y, x) - a(y, x)/mult) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
        END DO

        DEALLOCATE(a)
        DEALLOCATE(a_copy)

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